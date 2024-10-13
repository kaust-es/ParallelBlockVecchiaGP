//
// Created by dragos on 28/10/22.
//
#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <omp.h>
#include "initializer.h"

std::vector<Point> kmean_seq (std::vector<Point>& points, std::vector<Point>& centroids, int epochs, int k, int threads);

void kmean_par (std::vector<Point>& points, std::vector<Point>& centroids, int epochs, int k, int threads);
void kmean_par_earth (std::vector<Point>& points, std::vector<Point>& centroids, int epochs, int k, int threads);
#endif //KMEANS_H
