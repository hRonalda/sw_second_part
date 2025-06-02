
# SE4HPC DevOps Project

## Overview

This project addresses both parts of the **Software Engineering for HPC (SE4HPC)** DevOps assignment, covering:

- **Task 1**: Unit testing and CI pipeline using GitHub Actions  
- **Task 2 & 3**: Containerization (Singularity), job automation, and SLURM integration on **Galileo100** using CI/CD workflows

---

## Repositories

| Task | Link                                                                 |
|------|----------------------------------------------------------------------|
| Task 1 – Unit Testing & CI | [Repo Link](https://github.com/MarianoAkaMery/QiaoLibriciLiHuang_DevOps_first_part) |
| Task 2/3 – SLURM & Containerization | [Repo Link](https://github.com/MarianoAkaMery/QiaoLibriciLiHuang_DevOps_second_part) |

---

## 👥 Team Members

| Name                      | Person Code | Role |
|---------------------------|-------------|------|
| Salvatore Mariano Librici | 11078653    |  |
| Rong Huang                | 10948935    | Self-hosted runner version for step3|
| Yibo Li                   | 11022291    |  |
| Zhaochen Qiao             | 11021721    |  |

---

##  Task 1 — Unit Testing

### Description

We implemented Google Test cases to validate the `convert_grayscale` function. Tests include:

- Grayscale method correctness (Average, Luminosity, Lightness)
- Handling malformed input and edge cases
- Integration into CI pipeline for automatic test validation

### CI Pipeline (GitHub Actions)

- Triggered on push/pull request
- Builds with CMake + g++
- Runs Google Test and reports results

---

##  Task 2 & 3 — CI/CD with SLURM & Singularity

### Pipeline Steps

1. Checkout repo and submodules  
2. Install dependencies (Go, runc, Singularity)  
3. Build `.sif` from `Singularity.def`  
4. Run local grayscale conversion for validation  
5. Upload artifacts  
6. Use SSH to connect to Galileo100  
7. Transfer `.sif` and `job.sh`  
8. Submit job with `sbatch`

### Containerization

- Based on `Singularity.def`
- Includes grayscale source code, test binaries
- Mounted input/output folders
- Built within CI workflow

### SLURM Job Script

```bash
singularity exec ./grayscale.sif /opt/app/build/convert_grayscale input output Average
singularity exec ./grayscale.sif /opt/app/build/test_grayscale > grayscale_output.log 2>&1
```

---

##  Notable Challenges & Solutions

### 1. SSH Certificate Authentication on GitHub Runners

- **Problem**: The certificate generated via `step ssh certificate` requires a non-empty passphrase.
- **Issue**: GitHub-hosted runners do not allow interactive passphrase entry → SSH connection fails.
- **Solution**: We created a parallel pipeline using a **self-hosted runner** on local Ubuntu, enabling passphrase entry during runtime. This allowed:
  - Correct SSH login to Galileo100
  - Successful `.sif` and `job.sh` transfer
  - SLURM job submission

> See self-hosted version: [ci.yml](https://github.com/hRonalda/sw_second_part/blob/master/.github/workflows/ci.yml)

### 2. 

- 


---

## Summary

This project showcases full DevOps automation for HPC workloads:
- Unit-tested C++ grayscale converter
- Singularity-based container deployment
- CI/CD integration using GitHub Actions
- Automated SLURM job execution on Galileo100

---
