
/*
 * For this assigment you will write some functions that help 
 * accomplish the following procedure:
 * (1) Load an image from disk
 * (2) Perform linear-normalization on the image (formula given)
 * (3) Save the image in ppm format (this is done for you)
 *
 * You will also need to set up your own environment to run and test 
 * your code. No Makefile will be supplied. You must generate your own
 * testcases and make sure your code works yourself.
 *
 * Writing part (1) of this assignment is tricky, because you cannot
 * control data coming from outside of your program. Because you cannot 
 * control the data, you cannot trust it either, and so you must check 
 * _everything_. Just to be clear, you must check, ...
 * 
 *                        E.V.E.R.Y.T.H.I.N.G
 *
 * Most dangerous real-world computer bugs are related to programmers
 * not sufficiently checking the inputs to their programs. So for
 * this assignment, you will need to think very carefully about what
 * could go wrong when reading a file. If anything goes wrong, you
 * return NULL and leak no resources. In this way your code will be
 * bullet-proof; even a malicious user cannot crash your program.
 *
 * You are supplied with a few test images, including corrupt test 
 * images. These test-cases are provided in order to simplify and
 * standardise the assignment, and ease the learning process. However,
 * in real-world scenarios, you would need to generate your own
 * testcases, including corrupt test cases. By the end of this
 * assignment, you should understand how to go about doing that.
 *
 * Writing part (2) requires implementing a simple math formula to 
 * scale the intensity values in the input image. You have the
 * expected output files in the "expected" directories. You can
 * test if you have the correct solution by comparing your output
 * file with the "expected" directory.
 */

/*
 * == HINTS ==
 *
 * (1) Although a file is just a stream of bytes (1s and 0s), logically
 *     speaking, they are generally divided into a "header" structure 
 *     and a "data" structure. The "header" explains the layout of the
 *     "data".
 *
 * (2) When reading and writing binary files, it helps to look at the
 *     files in a hex-editor. Hex editors show a file as a sequence
 *     of hexidecimal (base-16) numbers. (If you don't yet understand
 *     base-16 notation, then now is a good time to learn this simple 
 *     and important concept.) You can ask emacs to show you the raw
 *     byte-structure of a file by using "hexl-mode". (M-x hexl-mode)
 *
 * (3) Write your own makefile -- you already have examples from 
 *     previous assignments. Your best of compiling your code with make
 *     but running tests by hand.
 *
 * (4) An alternative to Make is to simply write a bash script. This
 *     is extremely easy. A bash script is just a sequence of commands
 *     that you would otherwise type into the terminal. You put
 *     "#!/bin/bash" on the very first line, change the permission, and
 *     you are done.
 *
 * (5) Don't forget to run your code through valgrind. You must _never_
 *     leak memory.
 *
 * (6) You can compare two binary files using the "md5sum" program:
 *   
 *         > md5sum  expected/01-smile.ppm 
 *         b981173424d0ba22bf406fa0bf37cfe1 expected/01-smile.ppm
 *         > md5sum outputs/01-smile.ppm 
 *         b981173424d0ba22bf406fa0bf37cfe1 outputs/01-smile.ppm
 *
 *     If two files have _exactly_ the same bytes, then their md5sum
 *     will be the same. 
 *
 * (7) Don't leave this to the last minute.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pa06.h"

/*
 * ===================================================================
 * Load an image from disk in the "ece264" format. 
 *
 * The "ece264" image format supports 8-bit grayscale images. That 
 * means that every pixel in the image has a single 8-bit value 
 * (0..255), which denotes the intensity, or amount of whiteness at 
 * that pixel.
 *
 * The file has a 16 byte header whose binary layout is given by the 
 * struct ImageHeader in the file "pa06.h". The full explanation of 
 * this header is:
 *
 * + 4 byte integer: "magic number" 0x21343632. 
 *                   The first 4 bytes of the file always start with
 *                   this number (in little-endian format). If this
 *                   number is absent, then there is something wrong
 *                   with the file.
 * + 4 byte integer: width of the image
 * + 4 byte integer: height of the image
 * + 4 byte integer: length of an ASCII string file comment including
 *                   the NULL-byte
 *
 * The next N bytes is a null-termianted ASCII string. The length of
 * the string is specified in the last field of the header. The length
 * _includes_ the trailing NULL byte.
 *
 * After the ASCII string, there are width*height bytes of pixel data.
 * Each byte is /unsigned/, and represents the intensity of a pixel in
 * the range [0..255]. The intensity of the pixel is its "whiteness".
 * A value of 255 denotes a fully white pixel, and a value of 0
 * denotes a fully black pixel. 
 *
 * The pixels are stored in "row-major-order" from top-to-bottom. 
 * That means that the first byte if the intensity of pixel [0, 0], 
 * which is the top-left corner of the image. After reading "width" 
 * number of pixels, you will arrive at the start of the second row 
 * of pixels, which is the intensity of coordinate [0, 1]: the first
 * pixel of the second line of the image.
 *
 * In general, pixel[x, y] == image->data[x + y * width] where (x, y)
 * is the x-y co-ordinate of the pixel, with x increasing left-to-
 * right, and y increasing top-to-bottom.
 *
 * To complete this function, you must:
 * (1)  use fopen to open the file and check that the file was truly 
 *      opened
 * (2)  read the 16 byte header, checking that you actually read 16 
 *      bytes. (There is no guarantee that the input file is 16 bytes
 *      long.)
 * (3)  Check that the magic-bits match ECE264_IMAGE_MAGIC_BITS.
 * (4)  Check that the image width and height is sane. (i.e., > zero.)
 * (5)  Malloc memory for the comment. (The comment_len _includes_ the
 *      null byte on the string.)
 * (6)  Check that malloc returned a non-NULL pointer if comment_len
 *      is greater than zero.
 * (7)  Read the string from disk, checking that you read every byte
 *      successfully.
 * (8)  Malloc memory for the pixel data. There are width * height 
 *      pixels, and each pixel uses sizeof(uint8_t) bytes.
 * (9)  Read the pixel data from disk, making sure that you read every
 *      bytes successfully.
 * (10) Attempt to read one more pixel from file and check that this
 *      FAILS. (There should be no additional bytes at the end of the
 *      file.)
 * (11) If anything went wrong in steps (1-10), then you must clean up
 *      any resources used, and then return NULL. Otherwise you need 
 *      to allocate a struct Image pointer, fill in its values and 
 *      return it.
 * 
 * LEAK NO RESOURCES
 *
 * Good luck.
 */
struct Image * loadImage(const char* filename) //have to return an image pointer
{
  //LOCAL VARIABLE
  struct ImageHeader header; //initialization, just like int a
  FILE * fptr;
  struct Image * picture; //an image pointer

  //open the file using fopen and check if its really working
  fptr = fopen(filename, "rb"); //rb is reading the bytes
  if (fptr == NULL)
    {
      return NULL;
    }

  //read the 16 bytes header, check that you actually read 16 bytes
  if (fread(&header, sizeof(struct ImageHeader), 1, fptr) != 1) //fread returns how many times it reads the file, which in this case is one time! 
    //imageheader type has 16 bytes, thats why we only read it once
    { //getting the address of header and address is a pointer since the argument of fread is a pointer 
      fclose(fptr);     
      return NULL;
    }
  printf("\nasasfasf\n");
  //check that the magic bits match ECE264-IMAGE-MAGICBITS
  if (header.magic_bits != ECE264_IMAGE_MAGIC_BITS)
    {
      fclose(fptr);
      return NULL;
    }

  //check that the image width and height is sane (>0)
  if (header.width == 0 && header.height == 0)
    {
      fclose(fptr);
      return NULL;
    }

  //malloc memory for the comment(the comment_ len _include_ the nulll byte on the string)  
  picture = malloc(sizeof(struct Image));  
  picture -> comment = malloc(sizeof(char) * header.comment_len);

  //check that malloc returned a non NULL pointer if comment_len > 0
  if (picture -> comment == NULL)
    {
      free(picture);
      fclose(fptr);
      return NULL;
    }

  //read string from disk, checking that you read every byte succesfully
  if (fread(picture -> comment, sizeof(char), header.comment_len, fptr) != header.comment_len)//gonna return how many bytes I have read so it would be in integer , confused asked again tomorrow
    {
      free(picture -> comment);
      free(picture);
      fclose(fptr);
      return NULL;
    }
  //if(picture -> comment == NULL)
  //{ //dont forget to free it
  //RETURN null;
  //}
  //malloc memory for the pixel data. There are width * height pixels and each pixels use sizeof(unint8_t) bytes
  picture -> width = header.width; //if we want to access something from pointer structure, use an arrow
  picture -> height = header.height;
  printf("\nadsasaf\n");

  picture -> data = malloc(sizeof(uint8_t)*(picture -> width * picture -> height)); //uint8_t is unsigned integer 8 bits
  if(picture -> data == NULL)
    {
      free(picture -> comment);
      free(picture);
      fclose(fptr);
      return NULL;
    }  
//1 pixel is 1 byte
  //1 byte is 8 bits
  //the value of integers can be 0-255 for 8 bits, the normal integer is 4 bytes (32 bits), when we are using int, that means 4 byte of memory
  //read the pixel data from disk, check that you read every byte successfully
  if(fread(picture -> data, sizeof(uint8_t), picture -> width * picture -> height, fptr) != (picture -> width * picture -> height))
    {
      free(picture -> data);
      free(picture -> comment);
      free(picture);
      fclose(fptr);
      return NULL;
    }

  //attempt to read one more pixel from file and check that this fails as there shouldnt be any additional bytes at the end of file
  if(fread(picture -> data, sizeof(uint8_t), 1, fptr) == 1)
    {
      free(picture -> data);
      free(picture -> comment);
      free(picture);
      fclose(fptr);
      return NULL;
    }

  //If anything went wrong from 1-10, clean up any resources used and return null. Otherwise, allocate a struct image pointer, fill in its value and return it
  fclose(fptr);
  return picture;

  //two structures : iamge header and image, after we fread, all info will be store in imageheader atributes, arrow can only be ued when you strucutre is a pointer, have to use arrow, size of image structure
      //4 bytes is size of the type we dont know how many array of characters are inside that size
}


/*
 * ===================================================================
 * Free memory for an image structure
 *
 * loadImage(...) (above) allocates memory for an image structure. 
 * This function must clean up any allocated resources. If image is 
 * NULL, then it does nothing. (There should be no error message.) If 
 * you do not write this function correctly, then valgrind will 
 * report an error. 
 */

void freeImage(struct Image * image)
{ //just a pointer poiting to a chunk of memory
  //if its a null pointer i dont need to free it, i just need to return, since is void, no need to return anything   
if(image == NULL)
    {
      return;
    }
 free(image -> data);
 free(image -> comment);
 free(image);
 return;
}

/*
 * ===================================================================
 * Performs "linear normalization" on the passed image
 *
 * Imagine that the intensity values in your input image are in the 
 * range [50..180]. The image looks gray and washed out. You can 
 * "normalize" the image, which means apply some mathematical filter
 * that "stretches" the intensity values to give a more satisfying
 * image. We're going to use "linear normalization" which is the 
 * simplest normalization method. It works as follows:
 *
 * (1) Find the min and max intensity value of pixels in the image
 * (2) Now scale each pixel so that its new intensity is:
 *     
 *        pixel[i] = (pixel[i] - min) * 255.0 / (max - min)
 *
 * That's it! For the above example the equation is:
 *
 *        pixel[i] = (pixel[i] - 50) * 255.0 / (180 - 50)
 *
 * To implement this, you need two for loops, one after the other. 
 * The first for-loop completes step (1), and the second for-loop 
 * to complete step (2). 
 */
void linearNormalization(struct Image * image)
{
  //LOCAL VARIABLE
  uint8_t min = 0; //
  uint8_t max = 0;
  int i;
  int j;

  //FIND MAX AND MIN
  for (i = 1; i < (image -> width * image -> height); i++)  
    {
      if (i > 0)
	{
	  if(image -> data[i] > image -> data[i - 1])
	    {
	      max = image -> data[i];
	    }
	  if(image -> data[i] < image -> data[i - 1])
	    {
	      min = image -> data[i];
	    }
	}
    }

  for(j = 0; j < (image -> width * image -> height); j++)  
    { 
      image -> data[j] = (image -> data[j] - min) * 255.0 / (max - min);
    } 
}



