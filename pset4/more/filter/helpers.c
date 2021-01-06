#include "helpers.h"
#include <math.h>

// Convert image to grayscale
// To convert to greyscale you find the average of the values of RGB.
// Set the RGB values for each pixel to the average number.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iteration to scan every pixel.
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find the average value for RGB channels.
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Set each channel to the average number.
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
// To convert to Sepia you apply a formula for each channel.
// The values after the formula can not be more than 255.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iteration to scan every pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Apply the formula for each channel of the pixel.
            int blue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            int green = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int red = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            // Set each channel with the formula values rounded.
            // If the formula value is higher than 255, set the channel 255.
            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue;
            }
            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green;
            }
            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }
        }
    }
    return;
}

// Reflect image horizontally
// To reflect the image you swap the pixels horizontally.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iteration to scan every pixel.
    for (int i = 0; i < height; i++)
    {
        // Iteration to swap the pixels on the left with the pixels on the right.
        // As we want to reflect the image, we should stop swaping in the middle of the image.
        for (int j = 0; j < (width / 2); j ++)
        {
            // Create a temporal variable to store the value of of the left pixel.
            RGBTRIPLE temp = image[i][j];
            // Change the value of the left pixel with the value of the right pixel.
            image[i][j] = image[i][width - j - 1];
            // Change the value of the right pixel with the temporally stored value.
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
// To blur an image, you take the average RGB from the pixel's neigbors.
// Set the pixel RGB value to the average.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Vatiables to store the total values of each channel, and the neigbor pixel count.
    int sBlue, sGreen, sRed;
    float count;
    RGBTRIPLE temp[height][width];
    // Iteration to scan the pixels.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sBlue = 0;
            sGreen = 0;
            sRed = 0;
            count = 0.0;
            // Iteration to scan the pixel neigbors.
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Check for valid neigbor pixels.
                    // Check the pixels within the image boundaries.
                    if (i + h < 0 || j + w < 0 || i + h >= height || j + w >= width)
                    {
                        continue;
                    }
                    else
                    {
                        // Get the values of the neigbors RGB.
                        sBlue += image[i + h][j + w].rgbtBlue;
                        sGreen += image[i + h][j + w].rgbtGreen;
                        sRed += image[i + h][j + w].rgbtRed;
                        count ++;
                    }
                }
            }
            // Find the average value of each channel.
            temp[i][j].rgbtBlue = round(sBlue / count);
            temp[i][j].rgbtGreen = round(sGreen / count);
            temp[i][j].rgbtRed = round(sRed / count);
        }
    }
    // Set the average as RGB values of the pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
// To highlight the edges you apply the Sobel edge detection algorithm.
// The values after the formula can not be more than 255.
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // Set the Sobel operation matrix.
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Iterarion to scan for every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int xBlue = 0, xGreen = 0, xRed = 0;
            int yBlue = 0, yGreen = 0, yRed = 0;
            // Iteration to scan the pixel neigbors.
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Check for valid neigbor pixels.
                    // Check the pixels within the image boundaries.
                    if (i + h >= 0 && j + w >= 0 && i + h < height && j + w < width)
                    {
                        // Get the values of the neigbors RGB applying the Sobel matrix.
                        // Apply X matrix.
                        xBlue += Gx[h + 1][w + 1] * image[i + h][j + w].rgbtBlue;
                        xGreen += Gx[h + 1][w + 1] * image[i + h][j + w].rgbtGreen;
                        xRed += Gx[h + 1][w + 1] * image[i + h][j + w].rgbtRed;
                        // Apply Y matrix.
                        yBlue += Gx[w + 1][h + 1] * image[i + h][j + w].rgbtBlue;
                        yGreen += Gx[w + 1][h + 1] * image[i + h][j + w].rgbtGreen;
                        yRed += Gx[w + 1][h + 1] * image[i + h][j + w].rgbtRed;
                    }
                }
            }
            // Compute the new RGB values.
            // For each channel you calculate the Square root of Gx^2 + Gy^2.
            int blue = round(sqrt((xBlue * xBlue) + (yBlue * yBlue)));
            int green = round(sqrt((xGreen * xGreen) + (yGreen * yGreen)));
            int red = round(sqrt((xRed * xRed) + (yRed * yRed)));
            // Set each channel with the new values rounded.
            // If the formula value is higher than 255, set the channel 255.
            if (blue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            else
            {
                temp[i][j].rgbtBlue = blue;
            }
            if (green> 255)
            {
                temp[i][j].rgbtGreen = 255;
            }
            else
            {
                temp[i][j].rgbtGreen = green;
            }
            if (red > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
            else
            {
                temp[i][j].rgbtRed = red;
            }
        }
    }
    // Set the new values from the Sobel operator to the pixel RGB.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}