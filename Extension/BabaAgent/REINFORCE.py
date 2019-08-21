import torch
from torch import nn, optim
import torch.nn.functional as F
from torch.distributions import Categorical

import copy
import numpy as np

from Environment import BabaEnv10x10
import pyBaba

USE_CUDA = torch.cuda.is_available()
env = BabaEnv10x10()

class Network(nn.Module):
    def __init__(self):
        super(Network, self).__init__()

        self.conv1 = nn.Conv2d(pyBaba.Preprocess.TENSOR_DIM, 64, 3, padding=1)
        self.conv2 = nn.Conv2d(64, 64, 3, padding=1)
        self.conv3 = nn.Conv2d(64, 1, 1, padding=0)
        self.fc = nn.Linear(100, 5)

        self.log_probs = []
        self.rewards = []

    def forward(self, x):
        x = F.relu(self.conv1(x))
        x = F.relu(self.conv2(x))
        x = F.relu(self.conv3(x))

        x = x.view(x.data.size(0), -1)
        x = self.fc(x)

        return F.softmax(x, dim=1)

net = Network()
if USE_CUDA:
    net = net.cuda()

opt = optim.Adam(net.parameters(), lr=1e-2)

def get_action(state):
    state = torch.tensor(state)
    if USE_CUDA:
        state = state.cuda()

    policy = net(state)

    m = Categorical(policy)
    action = m.sample()

    net.log_probs.append(m.log_prob(action))
    return env.action_space[action.item()]

def train():
    R = 0

    loss = []
    returns = []

    for r in net.rewards[::-1]:
        R = r + 0.99 * R
        returns.insert(0, R)

    returns = torch.tensor(returns)
    returns = (returns - returns.mean()) / (returns.std() + 1e-5)

    for prob, R in zip(net.log_probs, returns):
        loss.append(-prob * R)

    opt.zero_grad()

    loss = torch.cat(loss).sum()
    loss.backward()

    opt.step()

    net.log_probs, net.rewards = [], []

if __name__ == '__main__':
    global_step = 0
    scores, episodes = [], []

    for e in range(10000):
        score = 0

        state = env.reset().reshape(1, -1, 10, 10)

        while not env.done:
            global_step += 1

            action = get_action(state)
            next_state, reward, done, _ = env.step(action)
            next_state = next_state.reshape(1, -1, 10, 10)

            net.rewards.append(reward)
            score += reward
            state = copy.deepcopy(next_state)

            if env.done:
                train()
                scores.append(score)

                print(f'Episode {e}: score: {score} time_step: {global_step}')
