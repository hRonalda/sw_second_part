#!/bin/bash

# Set job name
#SBATCH --job-name=grayscale_job       # Job name

# Redirect output and error
#SBATCH --output=grayscale.txt  # Output file
#SBATCH --error=grayscale.txt    # Error file

# Set Parameters
#SBATCH --time=0:10:00                   # Time Limit (hh:mm:ss)   
#SBATCH --ntasks=2                       # Number of tasks
#SBATCH --nodes=1                        # Number of nodes
#SBATCH --partition=g100_all_serial      # Partition to submit job

# Module Load for Singularity
module load singularity

# --------------------------------------------------------------------------------#
# This line is necessary to prevent "No Protocol specified" warning from appearing.
# --------------------------------------------------------------------------------#    
export HWLOC_COMPONENTS=-gl

# Set TMPDIR to a writable directory (have done mkdir ~/tmp in advance, no need to create) 
export TMPDIR=~/tmp

# Set Open MPI environment variables to use the TMPDIR, which is a writable directory.
export OMPI_MCA_tmpdir_base=$TMPDIR
export OMPI_MCA_orte_tmpdir_base=$TMPDIR
export OMPI_MCA_plm_rsh_agent="ssh :rsh"

# Set MPI to use TCP as the communication protocol
export OMPI_MCA_btl=self,tcp

# Ensure Singularity TMP and Cache directories are set to writable locations
export SINGULARITY_TMPDIR=$TMPDIR/singularity_tmp
export SINGULARITY_CACHEDIR=$TMPDIR/singularity_cache

# -----------------------------------------------------------------------------
# Compare two ways to run a singularity container.
# -----------------------------------------------------------------------------

# Run application outside singularity container (Just for fun)
srun singularity exec  ~/seproject/graysclae.sif mpiexec -np 2 ~/seproject/main

# -----------------------------------------------------------------------------
# Core Work Of This Job File: Do matrix multiplication by using MPI (2 tasks).
# Run application inside singularity container (which is demaned by the project)
# -----------------------------------------------------------------------------
singularity exec ~/seproject/grayscale.sif mpirun -np 2 /opt/QiaoLibriciLiHuang_DevOps_second_part/main
