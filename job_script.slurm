#!/bin/bash
#SBATCH --job-name=grayscale_job
#SBATCH --output=grayscale.out
#SBATCH --error=grayscale.err
#SBATCH --time=00:10:00
#SBATCH --partition=g100_all_serial
#SBATCH --ntasks=1
#SBATCH --nodes=1

module load singularity

singularity run ~/seproject/grayscale.sif input output Average
