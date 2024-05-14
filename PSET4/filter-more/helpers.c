#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE gray, rounded;

    gray.rgbtBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rounded.rgbtBlue = round(image[i][j].rgbtBlue);
            rounded.rgbtGreen = round(image[i][j].rgbtGreen);
            rounded.rgbtRed = round(image[i][j].rgbtRed);

            gray.rgbtBlue = round((rounded.rgbtBlue + rounded.rgbtGreen + rounded.rgbtRed) / 3.0);

            image[i][j].rgbtBlue = gray.rgbtBlue;
            image[i][j].rgbtGreen = gray.rgbtBlue;
            image[i][j].rgbtRed = gray.rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE aux;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            aux = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int totalBlue = 0, totalGreen = 0, totalRed = 0;
    float aux = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux = 0;
            totalBlue = 0;
            totalGreen = 0;
            totalRed = 0;
            for (int x = -1; x < 2; x++)
            {
                if (i + x > height - 1 || i + x < 0)
                {
                    continue;
                }
                for (int y = -1; y < 2; y++)
                {
                    if (j + y > width - 1 || j + y < 0)
                    {
                        continue;
                    }
                    else
                    {
                        totalBlue = totalBlue + image[i + x][j + y].rgbtBlue;
                        totalGreen = totalGreen + image[i + x][j + y].rgbtGreen;
                        totalRed = totalRed + image[i + x][j + y].rgbtRed;
                        aux = aux + 1;
                    }
                }
            }
            copy[i][j].rgbtBlue = round(totalBlue / aux);
            copy[i][j].rgbtGreen = round(totalGreen / aux);
            copy[i][j].rgbtRed = round(totalRed / aux);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int totalRedGx = 0, totalBlueGx = 0, totalGreenGx = 0, totalRedGy = 0, totalBlueGy = 0,
        totalGreenGy = 0, aux = 0;
    int red, blue, green;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totalRedGx = 0;
            totalRedGy = 0;
            totalGreenGx = 0;
            totalGreenGy = 0;
            totalBlueGx = 0;
            totalBlueGy = 0;
            aux = 1;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x > height - 1 || i + x < 0 || j + y > width - 1 || j + y < 0)
                    {
                        aux = aux + 1;
                        continue;
                    }
                    else
                    {
                        totalRedGx = totalRedGx + (image[i + x][j + y].rgbtRed * Gx[aux - 1]);
                        totalRedGy = totalRedGy + (image[i + x][j + y].rgbtRed * Gy[aux - 1]);

                        totalGreenGx = totalGreenGx + (image[i + x][j + y].rgbtGreen * Gx[aux - 1]);
                        totalGreenGy = totalGreenGy + (image[i + x][j + y].rgbtGreen * Gy[aux - 1]);

                        totalBlueGx = totalBlueGx + (image[i + x][j + y].rgbtBlue * Gx[aux - 1]);
                        totalBlueGy = totalBlueGy + (image[i + x][j + y].rgbtBlue * Gy[aux - 1]);
                        aux = aux + 1;
                    }
                }
            }
            blue = round(sqrt((totalBlueGx * totalBlueGx) + (totalBlueGy * totalBlueGy)));
            green = round(sqrt((totalGreenGx * totalGreenGx) + (totalGreenGy * totalGreenGy)));
            red = round(sqrt((totalRedGx * totalRedGx) + (totalRedGy * totalRedGy)));

            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }

            copy[i][j].rgbtBlue = blue;
            copy[i][j].rgbtGreen = green;
            copy[i][j].rgbtRed = red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
