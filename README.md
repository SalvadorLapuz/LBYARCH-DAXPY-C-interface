# Comparative Analysis of the Performance of the Kernels in x86-64 and C

## Introduction

<p align="justify"> This program seeks to determine the difference between the execution time of x86-64 assembly and the C programming language of a **DAXPY (A*X + Y)** function. The function can be seen below. </p>

![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/a2570851-c0ed-4cdc-b79a-6f8a18b10e77)

## Algorithm Implementation

<p align="justify"> The program includes a sanity check implementation in order to cross-check the resulting output of x86-64 assembly and C kernels. Suppose there are any inconsistencies between the outputs of these kernels throughout the validation process, suggesting a possible error. In that case, the program will instantly stop to ensure the integrity of the results. </p>

![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/3d354ba3-ea75-4406-a765-686e5b3c0aa8)



## Comparative Analysis of Average Execution Time
<p align="justify"> For the average execution time, the group exported the needed data to a **CSV file** to create a better visualization comparing the average execution time of x86-64 assembly and C kernels. The results are listed below. </p>

**Input Size 2<sup>20</sup>**

| Debug | Release  |
| ------- | --- |
| ![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/b8afca05-ce77-4231-a368-fc1bd34c78cc)| ![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/7f8b1ba1-9286-45e2-8598-d70203a6cc69)|

**Input Size 2<sup>24</sup>**
| Debug | Release  |
| ------- | --- |
|![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/a8dba83d-dae0-44ee-86f1-25e72dd07cb8)| ![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/99949004-9993-4deb-a220-46c913ac4317)|

**Input Size 2<sup>29</sup>**
| Debug | Release  |
| ------- | --- |
|![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/7be669f0-6bb3-4f8e-9b78-cf6922fb5058)|![image](https://github.com/SalvadorLapuz/LBYARCH-DAXPY-C-interface/assets/135326621/de707059-751f-44bd-be8d-d4794586286d)
|

<p align="justify"> Based on the analysis, the two configurations (Debug and Release Mode) have evident differences in terms of execution time. It can be noticeable that the debug mode configuration has a slower configuration time than the release mode due to its disabled optimizations. This signifies that the debug mode configuration aims to present a more accurate representation in terms of execution. Also, the x86-64 assembly has a consistently faster execution time than the c kernel when executed under debug mode, which could be possible because of the nature of the assembly language and the compiler's specialized optimizations. However, in release mode, the C kernel has consistently outperformed the x86-64 assembly kernel regarding average execution time. To sum it up, it can be observed that the average execution time of both kernels has an increasing trend as the input grows exponentially in both configurations. </p>







