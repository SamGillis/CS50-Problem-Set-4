#include "helpers.h"
#include <math.h>

//swap function
void swap(RGBTRIPLE *a, RGBTRIPLE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int i = 0; i < width; i++)
        {
            int j = round((image[y][i].rgbtBlue + image[y][i].rgbtGreen + image[y][i].rgbtRed) / 3.0);
            image[y][i].rgbtBlue = j;
            image[y][i].rgbtGreen = j;
            image[y][i].rgbtRed = j;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int i = 0; i < width; i++)
        {
            int sepiaRed = round(((image[y][i].rgbtBlue * .189) + (image[y][i].rgbtGreen * .769) + (.393 * image[y][i].rgbtRed)));
            int sepiaGreen = round(((image[y][i].rgbtBlue * .168) + (image[y][i].rgbtGreen * .686) + (.349 * image[y][i].rgbtRed)));
            int sepiaBlue = round(((image[y][i].rgbtBlue * .131) + (image[y][i].rgbtGreen * .534) + (.272 * image[y][i].rgbtRed)));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            image[y][i].rgbtBlue = sepiaBlue;
            image[y][i].rgbtGreen = sepiaGreen;
            image[y][i].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width / 2; y++)
        {
            swap(&image[i][y], &image[i][(width - y - 1)]);
        }
    }
}

//swap function
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE output[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int i = 0; i < width; i++)
        {
            int total = 1;
            int blue = image[y][i].rgbtBlue;
            int green = image[y][i].rgbtGreen;
            int red = image[y][i].rgbtRed;
            //far left
            if (i > 0)
            {
                blue = blue + image[y][i - 1].rgbtBlue;
                red = red + image[y][i - 1].rgbtRed;
                green = green + image[y][i - 1].rgbtGreen;
                total = total + 1;
            }
            //upper left
            if (i > 0 && y > 0)
            {
                blue = blue + image[y - 1][i - 1].rgbtBlue;
                red = red + image[y - 1][i - 1].rgbtRed;
                green = green + image[y - 1][i - 1].rgbtGreen;
                total = total + 1;
            }
            //upper middle
            if (y > 0)
            {
                blue = blue + image[y - 1][i].rgbtBlue;
                red = red + image[y - 1][i].rgbtRed;
                green = green + image[y - 1][i].rgbtGreen;
                total = total + 1;
            }
            //upper right
            if (y > 0 && i < width - 1)
            {
                blue = blue + image[y - 1][i + 1].rgbtBlue;
                red = red + image[y - 1][i + 1].rgbtRed;
                green = green + image[y - 1][i + 1].rgbtGreen;
                total = total + 1;
            }
            //far right
            if (i < width - 1)
            {
                blue = blue + image[y][i + 1].rgbtBlue;
                red = red + image[y][i + 1].rgbtRed;
                green = green + image[y][i + 1].rgbtGreen;
                total = total + 1;
            }
            //lower right
            if (y < height - 1 && i < width - 1)
            {
                blue = blue + image[y + 1][i + 1].rgbtBlue;
                red = red + image[y + 1][i + 1].rgbtRed;
                green = green + image[y + 1][i + 1].rgbtGreen;
                total = total + 1;
            }
            //lower middle
            if (y < height - 1)
            {
                blue = blue + image[y + 1][i].rgbtBlue;
                red = red + image[y + 1][i].rgbtRed;
                green = green + image[y + 1][i].rgbtGreen;
                total = total + 1;
            }
            //lower left
            if (y < height - 1 && i > 0)
            {
                blue = blue + image[y + 1][i - 1].rgbtBlue;
                red = red + image[y + 1][i - 1].rgbtRed;
                green = green + image[y + 1][i - 1].rgbtGreen;
                total = total + 1;
            }
            int b = round(((float) blue) / total);
            int r = round(((float) red) / total);
            int g = round(((float) green) / total);
            output[y][i].rgbtBlue = b;
            output[y][i].rgbtRed = r;
            output[y][i].rgbtGreen = g;
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int i = 0; i < width; i++)
        {
            image[y][i] = output[y][i];
        }
    }
    return;
}
