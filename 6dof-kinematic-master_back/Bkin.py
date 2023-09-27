import FK_module
import time

input_pose = [0, 35, 2, 3, 4, 5]  # Define your input data

# Record the start time
start_time = time.time()

# Call the function
output_joint = FK_module.SolveFK(input_pose)

# Record the end time
end_time = time.time()

# Calculate the execution time
execution_time = end_time - start_time

print("pose joint:", output_joint)
print("Execution time:", execution_time, "seconds")

