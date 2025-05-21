#!/bin/bash
#SBATCH --job-name=grayscale       # task name
#SBATCH --output=output_%j.log               # outputfile
#SBATCH --error=error_%j.log                 # error log
#SBATCH --nodes=1                            # node number
#SBATCH --ntasks=1                           # task number
#SBATCH --cpus-per-task=4                    
#SBATCH --mem=8G                             # mem for each node
#SBATCH --time=01:00:00                      # max runnign time
#SBATCH --partition=g100_all_serial      # Partition to submit job                

# Module Load for Singularity
module load singularity

# set variables
SIF_IMAGE="matrix_mult.sif"
APP_COMMAND="/app/matrix_mult --input data.in --output result.out"

# run Singularity container
singularity exec $SIF_IMAGE $APP_COMMAND
