//
// Created by dragos on 31/10/22.
//

#include <vector>
#include <omp.h>
#include "kmeans.h"

/*
 * This function implemts the kmeans algorithm
 * @param points: the vector of points to be clustered
 * @param centroids: the vector of centroids
 * @param epochs: the number of epochs
 * @param k: the number of clusters
 * @return a vector of centroids
 */
std::vector<Point> kmean_seq(std::vector<Point> &points, std::vector<Point> &centroids, int epochs, int k, int threads)
{

    std::vector<Point> new_centroids = std::vector<Point>(k, Point());
    std::vector<int> cluster_cardinality(k, 0);

    for (int i = 0; i < epochs; i++)
    {
        for (Point &p : points)
        {
            double distance = DBL_MAX;
            for (int i = 0; i < k; i++)
            {
                if (euclidean_dist(p, centroids[i]) < distance)
                {
                    distance = euclidean_dist(p, centroids[i]);
                    p.cluster = i;
                }
            }
            new_centroids[p.cluster] += p;
            cluster_cardinality[p.cluster]++;
        }

        for (int i = 0; i < k; i++)
        {
            new_centroids[i] /= cluster_cardinality[i];
        }
        centroids = new_centroids;
        new_centroids = std::vector<Point>(k, Point());
        cluster_cardinality = std::vector<int>(k, 0);
    }
    return centroids;
}

/*
 * This function implemts a parallel version of the kmeans algorithm
 * @param points: the vector of points to be clustered
 * @param centroids: the vector of centroids
 * @param epochs: the number of epochs
 * @param k: the number of clusters
 * @return a vector of centroids
 */
void kmean_par(std::vector<Point> &points, std::vector<Point> &centroids, int epochs, int k, int threads)
// float eps = 10e-6)
{

    std::vector<Point> new_centroids = std::vector<Point>(k, Point());
    std::vector<int> cluster_cardinality(k, 0);
    double difference = DBL_MAX;

    int points_per_thread = ceil(points.size() / threads);

    fprintf(stderr, "---------------------------------\n");


    for (int i = 0; i < epochs; i++)
    {
        if (i % 10 == 0)
        {
            fprintf(stderr, "K-means: %d rounds / %d finished. \n", i, epochs);
        }
#pragma omp parallel num_threads(threads)
        {
            std::vector<int> tmp_cluster_cardinality(k, 0);
            std::vector<Point> tmp_new_centroids(k, Point());

#pragma omp for nowait schedule(static, points_per_thread)
            for (Point &p : points)
            {
                double distance = euclidean_dist(p, centroids[0]);
                p.cluster = 0;
                for (int i = 1; i < k; i++)
                {
                    double tmp = euclidean_dist(p, centroids[i]);
                    if (tmp < distance)
                    {
                        distance = tmp;
                        p.cluster = i;
                    }
                }
                tmp_new_centroids[p.cluster] += p;
                tmp_cluster_cardinality[p.cluster]++;
            }

#pragma omp critical
            {
                for (int i = 0; i < k; i++)
                {
                    new_centroids[i] += tmp_new_centroids[i];
                    cluster_cardinality[i] += tmp_cluster_cardinality[i];
                }
            }
        }

        for (int i = 0; i < k; i++)
        {
            if(cluster_cardinality[i] == 0){
                // option 1: we randomly choose other points a the initial cluster
                std::mt19937 gen(42);
                std::uniform_int_distribution<> distr(0, points.size() - 1);
                int random_number = distr(gen);

                new_centroids[i] += points[random_number];
                points[random_number].cluster = i;
                cluster_cardinality[i] += 1;
            }
            new_centroids[i] /= cluster_cardinality[i];
            difference += euclidean_dist(new_centroids[i], centroids[i]);
        }
        difference /= k;
        centroids = new_centroids;

        new_centroids = std::vector<Point>(k, Point());
        cluster_cardinality = std::vector<int>(k, 0);
    }

    // return centroids;
}