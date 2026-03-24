import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3' 
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
import numpy as np

model = Sequential([
    tf.keras.Input(shape=(400,)),
    Dense(25, activation='sigmoid'),
    Dense(15, activation='sigmoid'),
    Dense(1, activation='sigmoid')
])

print("Checking attributes after Input definition:")
try:
    print(f"model.input: {model.input}")
except Exception as e:
    print(f"model.input failed: {e}")

try:
    print(f"model.input_shape: {model.input_shape}")
except Exception as e:
    print(f"model.input_shape failed: {e}")

print("\nCalling model on dummy data...")
model(np.zeros((1, 400)))

try:
    print(f"model.input after call: {model.input}")
    print(f"model.input.shape: {model.input.shape}")
except Exception as e:
    print(f"model.input after call failed: {e}")
