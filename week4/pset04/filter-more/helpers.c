#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average_f = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int average_rounded_int = round(average_f);

            image[i][j].rgbtBlue = average_rounded_int;
            image[i][j].rgbtGreen = average_rounded_int;
            image[i][j].rgbtRed = average_rounded_int;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // gives last position
        int k = width - 1;
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = tmp;
            // decrements from last postion
            k -= 1;
        }
    }

    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }

    float box;
    int average_blue, average_green, average_red;

    // change the rgb values of the new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average_blue = 0;
            average_green = 0;
            average_red = 0;
            box = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (k + i < 0 || k + i > height - 1 || l + j < 0 || l + j > width - 1)
                    {
                        continue;
                    }
                    average_blue += image[i + k][j + l].rgbtBlue;
                    average_green += image[i + k][j + l].rgbtGreen;
                    average_red += image[i + k][j + l].rgbtRed;
                    box++;
                }
            }
            new_image[i][j].rgbtBlue = round(average_blue / box);
            new_image[i][j].rgbtGreen = round(average_green / box);
            new_image[i][j].rgbtRed = round(average_red / box);
        }
    }

    // change the values of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = image[i][j];
        }
    }

    float blue_x, green_x, red_x, blue_y, green_y, red_y;
    double blue_z, green_z, red_z;
    
    // change the rgb values of the new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue_z = 0; blue_y = 0; blue_x = 0;
            green_z = 0; green_y = 0; green_x = 0;
            red_z = 0; red_y = 0; red_x = 0;

            int Gx[3][3] = {{-1, 0, 1},
                            {-2, 0, 2},
                            {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1},
                            { 0,  0,  0},
                            { 1,  2,  1}};

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (k + i < 0 || k + i > height - 1 || l + j < 0 || l + j > width - 1)
                    {
                        continue;
                    }
                    // Gx direction values
                    red_x += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                    green_x += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                    blue_x += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;

                    // Gy direction values
                    red_y += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                    green_y += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                    blue_y += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;

                }
            }
            // square root sum of Gx and Gy values for every pixel and its rgb value
            red_z = sqrt(red_x * red_x + red_y * red_y);
            if (red_z > 255)
                red_z = 255;

            green_z = sqrt(green_x * green_x + green_y * green_y);
            if (green_z > 255)
                green_z = 255;

            blue_z = sqrt(blue_x * blue_x + blue_y * blue_y);
            if (blue_z > 255)
                blue_z = 255;

            new_image[i][j].rgbtBlue = (int) round(blue_z);
            new_image[i][j].rgbtGreen = (int) round(green_z);
            new_image[i][j].rgbtRed = (int) round(red_z);
        }
    }

    // change the values of original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}
