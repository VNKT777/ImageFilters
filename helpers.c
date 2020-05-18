#include "helpers.h"
#include<math.h>
#include<stdio.h>
/*
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
*/
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i < height; i++)
    {
        
        for(int j=0; j < width; j++ )
        
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
            
        }
        
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
/*
  rgbtRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  rgbtGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  rgbtaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
*/
    for (int i=0; i < height; i++)
    {
        
        for(int j=0; j < width; j++ )
        
        {
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed; 

            float RgbtRed = (0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            float RgbtGreen =(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            float RgbtBlue = (0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            
            if(RgbtRed >= 255)
            {
                image[i][j].rgbtRed = 255;    
            }
            else
            {
                image[i][j].rgbtRed = round(RgbtRed);
            }
            
            if(RgbtBlue >= 255)
            {
                image[i][j].rgbtBlue = 255;    
            }
            else
            {
                image[i][j].rgbtBlue = round(RgbtBlue);
            }
            
            if(RgbtGreen >= 255)
            {
                image[i][j].rgbtGreen = 255;    
            }
            else
            {
                image[i][j].rgbtGreen = round(RgbtGreen);
            }
        }
        
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int j=0,n=width/2; j<n; j++)
    {
        for(int i=0;i < height; i++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image1[height][width];
    
    for (int i=0; i < height; i++)
    {
        
        for(int j=0; j < width; j++ )
        
        {
            image1[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image1[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image1[i][j].rgbtRed = image[i][j].rgbtRed;
        }
        
    }
    
    for(int i=0; i < height; i++)
    {   
        for(int j=0; j< width; j++)
        {
            
            float Red = 0.0;
            float Green = 0.0;
            float Blue = 0.0;
            float count = 0.0;
            
            int Si=i-1;

            
            
            //For the matrix around the individual bit
            while(Si < i+2)
            {
                int Sj=j-1;
                while(Sj < j+2)
                {
                    if(Si == -1)
                    {
                        Si++;
                    }
                    if(Sj == -1)
                    {
                        Sj++;
                    }
                    if(Sj == width)
                    {
                        //printf("WIDTH");
                        break;
                    }
                    if(Si == height)
                    {
                        //printf("Height");
                        break;
                    }
                    
                    Red += image1[Si][Sj].rgbtRed;
                    Green += image1[Si][Sj].rgbtGreen;
                    Blue += image1[Si][Sj].rgbtBlue;
                    count++;

                    Sj++;
                }
                Si++;
            }
            printf("%f",count);
            
            image[i][j].rgbtBlue = round(Blue/count);
            image[i][j].rgbtGreen = round(Green/count);
            image[i][j].rgbtRed = round(Red/count);
        }
    }
    //printf("God Bless");
    return;
}
