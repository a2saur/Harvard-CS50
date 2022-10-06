#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_color;
    int value;
    float sum;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            sum = image[y][x].rgbtRed + image[y][x].rgbtGreen + image[y][x].rgbtBlue;
            value = round(sum / 3);
            new_color.rgbtRed = value;
            new_color.rgbtGreen = value;
            new_color.rgbtBlue = value;
            image[y][x] = new_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < (int) width / 2; x++)
        {
            temp = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    float sumR;
    float sumG;
    float sumB;
    int total;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            total = 0;
            sumR = 0;
            sumG = 0;
            sumB = 0;
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (y + a >= 0 && y + a < height && x + b >= 0 && x + b < width)
                    {
                        sumR += image[y + a][x + b].rgbtRed;
                        sumG += image[y + a][x + b].rgbtGreen;
                        sumB += image[y + a][x + b].rgbtBlue;
                        total++;
                    }
                }
            }
            new_image[y][x].rgbtRed = round(sumR / total);
            new_image[y][x].rgbtGreen = round(sumG / total);
            new_image[y][x].rgbtBlue = round(sumB / total);
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = new_image[y][x];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    float sumRx;
    float sumGx;
    float sumBx;
    float sumRy;
    float sumGy;
    float sumBy;
    float temp;

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1},
    };
    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
    };

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            sumRx = 0;
            sumGx = 0;
            sumBx = 0;

            sumRy = 0;
            sumGy = 0;
            sumBy = 0;
            // go through surrounding
            for (int a = -1; a < 2; a++)
            {
                for (int b = -1; b < 2; b++)
                {
                    if (y + a >= 0 && y + a < height && x + b >= 0 && x + b < width)
                    {
                        sumRx += image[y + a][x + b].rgbtRed * gx[a + 1][b + 1];
                        sumGx += image[y + a][x + b].rgbtGreen * gx[a + 1][b + 1];
                        sumBx += image[y + a][x + b].rgbtBlue * gx[a + 1][b + 1];

                        sumRy += image[y + a][x + b].rgbtRed * gy[a + 1][b + 1];
                        sumGy += image[y + a][x + b].rgbtGreen * gy[a + 1][b + 1];
                        sumBy += image[y + a][x + b].rgbtBlue * gy[a + 1][b + 1];
                    }
                }
            }
            temp = pow(sumRx, 2) + pow(sumRy, 2);
            temp = sqrt(temp);
            if (temp > 255)
            {
                temp = 255;
            }
            new_image[y][x].rgbtRed = round(temp);

            temp = pow(sumGx, 2) + pow(sumGy, 2);
            temp = sqrt(temp);
            if (temp > 255)
            {
                temp = 255;
            }
            new_image[y][x].rgbtGreen = round(temp);

            temp = pow(sumBx, 2) + pow(sumBy, 2);
            temp = sqrt(temp);
            if (temp > 255)
            {
                temp = 255;
            }
            new_image[y][x].rgbtBlue = round(temp);
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = new_image[y][x];
        }
    }
    return;
}