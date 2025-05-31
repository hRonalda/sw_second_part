## Additional Pipeline Version (Self-Hosted Runner)

In addition to the main pipeline implemented using GitHub-hosted runners, I developed an alternative version based on a **self-hosted runner**.

This was necessary due to a critical issue related to SSH authentication with CINECA. Specifically, the SSH certificate generated using `step ssh certificate` must be encrypted with a **non-empty passphrase**, and CINECA does not support passphraseless certificates.

GitHub-hosted runners do not allow interactive passphrase input during runtime. As a result, any SSH connection attempt fails with an error like:# sw_second_part# retry

This issue cannot be resolved on GitHub-hosted runners.

To overcome it, I switched to running the pipeline locally on a self-hosted Ubuntu machine, where the passphrase could be manually entered. This allowed me to:
- Use the SSH key and certificate pair successfully
- Connect to CINECA via SSH
- Transfer Singularity images
- Submit SLURM jobs

> ATTENTION:  This version is not the final submitted one but serves as documentation of an attempted solution to the SSH certificate challenge.
