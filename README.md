# Block Vecchia Algorithm for Estimation and Prediction

## ⚠️ Project Notice

**Important: Active development has moved to a new repository:**

<<<<<<< Updated upstream
👉 **[ExaGeoStatCPP](https://github.com/kaust-es/ParallelVecchiaGP)**

The codebase has been migrated from C to C++ as part of this transition.

The new version also includes support for R package installation.
=======
👉 **[ParallelVecchiaGP](https://github.com/kaust-es/ParallelVecchiaGP)**

>>>>>>> Stashed changes

This repository is now archived and no longer maintained.

---

## Introduction

The Block Vecchia Algorithm is a computational method for efficient spatial statistics calculations, designed for high-performance computing environments. This project includes implementations for both estimation and prediction tasks, leveraging GPU acceleration and optimized libraries. [paper: Block Vecchia Approximation for Scalable and Efficient Gaussian Process Computations
](https://www.tandfonline.com/doi/full/10.1080/00401706.2025.2475784)

## Installation and Compilation

### Prerequisites

Ensure you have the following libraries installed and their paths included in your system's PATH and LD_LIBRARY_PATH:

- GCC 10.2.0 or later
- CUDA 11.4 or later
- Intel MKL 2022.2.1 or later
- MAGMA 2.7.0 or later
- GSL 2.6 or later
- NLopt v2.7.1 or later
- OpenMP 4.1.0 or later
- BLAS

On Ubuntu or Debian-based systems, you can install some of these dependencies with (prediction only):

```bash
sudo apt-get install libgsl-dev libblas-dev libopenmpi-dev
```

### Compilation

To compile the project, navigate to the project root directory and run:

```bash
make
```

This will create the necessary executables in the `bin` directory.

## Usage

The main executable for the Block Vecchia Algorithm estimation is `test_dvecchia_batch`. Here are some example use cases:

1. View Help Information:
```bash
cd estimation
./bin/test_dvecchia_batch --help
```

2. Performance Test:
```bash
./bin/test_dvecchia_batch --ikernel 1.5:0.1:0.5 --kernel univariate_matern_stationary_no_nugget --num_loc 20000 --perf --vecchia_cs 300 --vecchia_bc 1500 --knn --seed 0
```

3. Simulated Data or Real Dataset:
```bash
./bin/test_dvecchia_batch --ikernel ?:?:? --vecchia_bc 300 --kernel univariate_matern_stationary_no_nugget --num_loc 20000 --vecchia_cs 150 --knn --xy_path /path/to/locations --obs_path /path/to/observations
```

## Output

Results are stored in the `./log` directory after execution.

## License

This project is licensed under the terms of the Apache License 2.0. See the LICENSE file for details.

---

### How to reproduce the results from the paper

The following scripts and notebooks are used to generate the corresponding figures. In our experiments, we use 40 CPU cores (Intel(R) Xeon(R) Gold 6230R CPU @ 2.10GHz) and NVIDIA V100 GPU 32GB.

 - Step 0: choose estimation or prediction, and download the bash and jupyter notebooks.
 - Step 1: use the bash script to run the experiments.
 - Step 2: use the notebook to process the results and generate the figures.

**Note:**
- The bash scripts and jupyter notebooks should be in the same folder with `estimation` or `prediction`.
- If there is no `log` and `fig` folder in the current directory, please create one.
- The well-trained model will be saved in the `log` folder, you can put them in corresponding `log` folders and visualize, see [here](https://www.dropbox.com/scl/fi/n00wjy0b5ja4q5x0qj22m/log.zip?rlkey=0ue47aieablekltedpql9nzbb&st=0rfce8in&dl=0).

For example of estimation
```
cd estimation
wget -O exe-estimation.zip https://www.dropbox.com/scl/fo/tkwnos3to038z945ys64u/ABqbicVRNfrXwaCu9N7CnsY?rlkey=mjytdqyadqzbksrkq86uyrr99&st=6620p253&dl=0
unzip exe-estimation.zip -d ./
rm exe-estimation.zip
mv exe-estimation/* ./
bash test_kl.sh
```
Lastly, please use the `./test_kl_plot.ipynb` to visualize the results. Prediction bash scripts are the same as the estimation and its link is [here](https://www.dropbox.com/scl/fo/tsxsyxf1whzgtfvdhd9yc/AFMFTMoKdYv1OespxmOn1yM?rlkey=k3uf3klc9bwa8utwibr0nsri1&st=otkfmpb1&dl=0).

##### Meta info for Estimation

- `blockVecchia` is used for block Vecchia estimation.

| Script/Notebook | Corresponding Figure(s) | Training Time | Comments |
| --------------- | ------------------------ | ------------- | -------- |
| `estimation/cluster.sh` / `estimation/cluster-reordering.ipynb` | Figure 2 | Instantly | |
| `estimation/memory.ipynb` | Figure 4 | Instantly |
| `estimation/test_kl.sh` / `estimation/test_kl_plot.ipynb` | Figure 5(a), Figures S1, S2, S3 | 30 mins |
| `estimation/test_kl.sh` / `estimation/test_kl_plot_blockcount_cs.ipynb` | Figure 5(b) | 30 mins |
| `estimation/test_kl.sh` / `estimation/test_kl_plot.ipynb` | Figure 6 | 30 mins |
| `estimation/test_kl.sh` / `estimation/test_kl_plot_time.ipynb` | Figure 7, Figure S4 | 30 mins |
| `estimation/test_simulation.sh` / `estimation/test_simulation.ipynb` | Figure 8, Figures S6, S7, S8 | 28 hours | |
| `estimation/real_soil.sh` / `estimation/real_wind.sh` / `estimation/real_dataset_soil_wind.ipynb` | Figures 11, 12 | 3 hours | set folder in Jupyter notebook for soil/wind results |
| `estimation/real_windspeed_3D.sh` / `estimation/real_windspeed_3D.ipynb` | Figure 13 (a), (b), (c) | 12 hours | |
| `estimation/test_kl_largeN.sh` / `estimation/test_kl_largeN.ipynb` / `estimation/test_kl_largeN_time.ipynb` | Figure S5 | 15 mins | |
| `estimation/real_soil_full.sh` / `estimation/real_dataset_soil-2m.ipynb` | Figure S11 | 24 hours |
| `estimation/test_kl_small.sh` / | Figure S14, S15, S16 | 10 mins |

##### Meta info for Prediction

| Script/Notebook | Corresponding Figure(s) | Training Time |
| --------------- | ------------------------ | ------------- |
| `prediction/pred_interval_simu.sh` / `prediction/plot_simu_pred.ipynb` | Figure 9, Figure S9 | 3.5 hours |
| `prediction/prediction_3d.sh` / `prediction/plot_realdata_pred.ipynb` | Figure 13 (d) | 10 hours |
| `prediction/prediction_2d.sh` / `prediction/plot_realdata_pred.ipynb` | Figures S12, S13 | 7.5 hours |
