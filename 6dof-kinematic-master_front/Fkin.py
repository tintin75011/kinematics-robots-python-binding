import FK_module
import time

input_joint = [34, -277, -131, -143, -313, -321]  # Define your input data

# Record the start time
start_time = time.time()

output_pose = FK_module.SolveFK(input_joint)
# Record the end time
end_time = time.time()

# Calculate the execution time
execution_time = end_time - start_time

print("Output pose:", output_pose)
print("Execution time:", execution_time, "seconds")
