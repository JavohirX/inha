# -*- coding: utf-8 -*-

"""

Created on Sat Apr  1 12:13:21 2023


@author: sarva

"""

import numpy as np

import matplotlib.pyplot as plt



"""

If price is modelled as ABM, sigma is estimated from historical prices as follows:

    sigma = sqrt((1/n)*sum((price[i] - price[i-1] - mu*dt)^2)/dt)

    mu - is a risk-free rate, usually refers to some risk-free investment. In other words, what is the safest profit you could make at time T if not buy this asset now.

"""


# random walk starts from 100, and goes up or down by 1 by toss of a fair coin

def rand_walk(x0=100, n_steps=100):

    # Initialize arrays

    x = np.zeros(n_steps)

    t = np.zeros(n_steps)


    x[0] = x0


    # Generate steps

    dW = np.random.uniform(0.0, 1.0, size=n_steps)


    # Simulate Arithmetic Brownian Motion

    for i in range(1, n_steps):

 
        if dW[i] >= 0.5:

            x[i] = x[i-1] + 1

        else:

            x[i] = x[i-1] - 1

        t[i] += i


    return x, t


# abm with 10% growth for the entire period and 5 points daily volatility

def abm(x0=100, mu=10, sigma=5, n_steps=100):


    delta_t = 1.0/n_steps

    mu_per_step = mu / n_steps


    # Initialize arrays

    x = np.zeros(n_steps)

    t = np.zeros(n_steps)


    x[0] = x0


    # Generate increments

    dW = np.sqrt(delta_t) * np.random.normal(size=n_steps)


    # Simulate Arithmetic Brownian Motion

    for i in range(1, n_steps):

        x[i] = x[i-1] + x[i-1]*mu_per_step*delta_t + sigma*dW[i]

        t[i] = t[i-1] + delta_t


    return x, t


# gbm with 10% growth for the entire period and 5% daily volatility

 
def gbm(x0=100, mu=10, sigma=0.05, n_steps=100):

    delta_t = 1.0/n_steps

    mu_per_step = mu / n_steps


    # Initialize arrays

    x = np.zeros(n_steps)

    t = np.zeros(n_steps)


    x[0] = x0


    # Generate increments

    dW = np.sqrt(delta_t) * np.random.normal(size=n_steps)


    # Simulate Geometric Brownian Motion

    for i in range(1, n_steps):

        x[i] = x[i-1] * np.exp(mu_per_step*delta_t + sigma*dW[i])

        t[i] = t[i-1] + delta_t


    return x, t



x, t = rand_walk()


# Plot the simulation

plt.plot(t, x)

plt.xlabel('Time')

plt.ylabel('Arithmetic Brownian Motion')

plt.title('Arithmetic Brownian Motion Simulation')

plt.show()