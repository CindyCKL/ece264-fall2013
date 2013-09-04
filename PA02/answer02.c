

#include "pa02.h"

/**
 * Count the number of characters in a null-terminated string 's' 
 * (not counting the null character).
 *
 * Example: my_strlen("foo") should yield 3.
 */
int my_strlen(const char * s)
{
  //LOCAL VARIABLE  
  int lcv = 0; //loop control expression, indicates the length of the array
  
  //CALCULATIONS
  while (s[lcv] != '\0') //as long as its not the ending of the array which is stated with '/0', lcv will keep increasing until it runs all elements in the array
    {
      lcv++;
    }
  return lcv;
}

/**
 * Count the number of occurrences of a particular character 'c' in a
 * null-terminated string 's'.
> *
 * Example: my_countchar("foo", 'o') should yield 2.
 */
int my_countchar(const char * s, char c)
{
   //LOCAL VARIABLE
  int i = 0; //loop control expression
  int occur = 0;  //how many c occurs in the string s
  int length = 0; //length of the array

  //CALCULATIONS
  length = my_strlen(s);
  for (i = 0; i < length; i++)
    {
      if(s[i] == c)
	{
	  occur++;
	 }
    }
         
  return occur;
}

/**
 * Convert an entire null-terminated string 's' to uppercase.  Only
 * alphabetical characters should be converted; numbers and symbols
 * should not be affected.  Hint: toupper(c) is a macro that yields
 * the uppercase version of a character c.
 *
 * Example: char foobar[10] = "foobar";
 * my_strupper(foobar) yields "FOOBAR".
 */
void my_strupper(char * s)
{
  //LOCAL VARIABLE
  int i; //loop control expression
  int length = 0; //length of the array

    //CALCULATIONS
    length = my_strlen(s);
    for (i = 0; i < length; i++)
    {
      s[i] = toupper(s[i]); //changing all the lowercase to uppercase
    }

}

/**
 * Convert an entire null-terminated string 's' to lowercase.  Only
 * alphabetical characters should be converted; numbers and symbols
 * should not be affected.  Hint: tolower(c) is a macro that yields
 * the lowercase version of a character 'c'.
 *
 * Example: char foobar[10] = "FOOBAR";
 * my_strupper(foobar) yields "foobar".
 */
void my_strlower(char * s)
{
  //LOCAL VARIABLE
  int i; //loop control expression
  int length = 0; //length of the string

  //COMPUTATIONS
  length = my_strlen(s); 
  for (i = 0; i < length; i++)
    {
      s[i] = tolower(s[i]);
    }
}

/**
 * Copy the contents of a null-terminated string 's2' into the memory
 * pointed to by 's1'.  Any existing data in 's1' will be overwritten by
 * the contents of 's2'.  Note: you can assume that there is sufficient
 * memory available in 's1'.  Hint: Don't forget to terminate the new
 * string with '\0'!
 * 
 * Example: char foo[10];
 * my_strcpy(foo, "foo") yields "foo".
 */
void my_strcpy(char * s1, const char * s2)
{
  //LOCAL VARIABLE
  int i; //loop control expression
  int length1; //length of array 1
  int length2; //length of array 2

  //COMPUTATIONS
  length1 = my_strlen(s1);
  length2 = my_strlen(s2);
  for(i = 0; i < length2; i++)
    {
      s1[i] = s2[i]; //overwrite all contents in s1 with s2
    }
  s1[length2] = '\0'; //ending the array

}

/**
 * Copy the first 'n' characters of a null-terminated string 's2' into the
 * memory pointed to by 's1'. Any existing data in 's1' will be
 * overwritten by the contents of 's2'.  Note: you can assume that there
 * is sufficient memory available in 's1'.  Hint: Don't forget to
 * terminate the new string with '\0'!
 * 
 * Example: char foo[10];
 * my_strncpy(foo, "foo", 1) yields "f".
 */
void my_strncpy(char * s1, const char * s2, int num)
{
  //LOCAL VARIABLE
  int i; //loop control expression

  //COMPUTATIONS
  for (i = 0; i < num; i++)
    {
      s1[i] = s2[i]; //overwrite all contents even if num < length1
    }
  s1[num] = '\0'; //ending the array  
}


/** 
 * Concatenate (append) the contents of a null-terminated string 's2'
 * onto the end of the null-terminated string 's1'.  Note: you can
 * assume that there is sufficient memory available in 's1'.  Hint:
 * Don't forget to terminate the new string with '\0'!
 * 
 * Example: char foo[10] = "foo";
 * my_strcat(foo, "bar") yields "foobar".
 */
void my_strcat(char * s1, const char * s2) 
{
   //LOCAL VARIABLE
  int i; //loop control expression
  int length1; //length of array1
  int length2; //length of array2

  //COMPUTATIONS
  length1 = my_strlen(s1);
  length2 = my_strlen(s2);
  for (i = 0; i < length2; i++)
    {
      s1[i + length1] = s2[i];// the content of array 2 will follow along the string 1
    }
  s1[i + length1] = '\0';
}


/** 
 * Concatenate (append) the first n characters of a null-terminated
 * string 's2' onto the end of the null-terminated string 's1'.  Note: you
 * can assume that there is sufficient memory available in 's1'.  Hint:
 * Don't forget to terminate the new string with '\0'!
 * 
 * Example: char foo[10] = "foo";
 * my_strcat(foo, "bar", 1) yields "foob".
 */
void my_strncat(char * s1, const char * s2, int num)
{
  //LOCAL VARIABLE
  int i; //loop control expression
  int length1; //length of array 1

  //COMPUTATIONS
  length1 = my_strlen(s1);
  for(i = 0; i < num; i++)
    {
      s1[ i + length1] = s2[i];
    }
  s1[i + length1] = '\0'; //i would be more than 0 at this point because its already gone the loop   
}

/**
 * Return a pointer to the first occurrence of a null-terminated
 * substring 's2' in a null-terminated string 's1'.  If 's2' does not appear
 * in 's1', the empty (NULL) pointer is returned.
 * 
 * Example: my_strstr("hello world!", "test") will yield 0 (NULL).
 * Example(2): my_strstr("foobar", "bar") will yield a pointer to the
 * "bar" portion of the "foobar" argument.
 */

const char *my_strstr(const char * s1, const char * s2)
{
   //LOCAL VARIABLE
  int i = 0; //for array 2
  int j = 0; //for array 1
  const char *ptr; //pointer that will be returned
  int length1 = 0; //length of array 1
  int length2 = 0; //length of array 2
 
  //COMPUTATIONS
  length1 = my_strlen(s1);
  length2 = my_strlen(s2);
  
  for(j = 0; j < length1; j++)
    {
      if (s1[j] == s2[i])
	{
	  ptr = &s1[j]; 
	  i++;
	}
      else
	{
	  ptr = NULL;	      
	  i = 0;
	}
    }

  if (i == length2) //means all the string in array 2 present in array 1
    {
      return  ptr;
    }
  else
    {
      return NULL;
    }
}

/**
 * Insert a null-terminated string s2 in the null-terminated string s1
 * at position pos.  All characters following position pos in s1 will
 * be moved to follow directly after the inserted characters from s2;
 * no characters will be overwritten.  Note: you can assume that there
 * is sufficient memory available in s1.
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos to its new location
 * starting from the back of the string and going forwards.
 * 
 * Insertions should happen BEFORE the character position referenced
 * by pos.  In other words, inserting s2 at position 0 (the first
 * character of a string) in s1 is equivalent to the string s2
 * followed by string s1.
 * 
 * If the character position pos is higher (or equivalent to) the
 * length of string s1, s2 will simply be appended to the end of s1
 * (i.e. it is equivalent to my_strcat(s1, s2);
 * 
 * Example: char foo[10] = "foo";
 * my_strinsert(foo, "bar", 0) yields "barfoo".
 * 
 * Example(2): char foo[10] = "foo";
 * my_strinsert(foo, "bar", 100) yields "foobar".
 */
void my_strinsert(char *s1, const char *s2, int pos)
{
  //LOCAL VARIABLES
  int i; //indeks for array1
  int j = 0; //indeks for array2 
  int length2; //length for array 2
  int length1; //length for array 1

  //COMPUTATIONS                          
  length1 = my_strlen(s1);
  length2 = my_strlen(s2);

  j = length1 - 1;
  for (i = (length2 + length1 - 1); i >= (pos + length2); i--)
    {
      s1[i] = s1[j]; //starting to copy elements from s1 from the very back 
      j--;
    }

  j = 0;
  for ( i = pos; i < (pos + length2); i++)
    {
      s1[i] = s2[j]; //copy elements s2 to s1, no elements in s1 overwritten since they are alredy copied
        j++;
    }
   s1[length1 + length2] = '\0';
}

/**
 * Delete a portion of the null-terminated string s that starts at
 * character position pos and is length characters long.  All
 * characters following position pos + length in s will be moved up to
 * follow directly after the characters before position pos. 
 * 
 * Hint: there is no need to create any temporary memory; simply copy
 * the contents of the string after position pos + length to their new
 * location.
 * 
 * Deletions should happen BEFORE the character position referenced by
 * pos.  In other words, deleting position 0 (the first character of a
 * string) in s means will start deleting from the first character.
 *
 * If the character position pos is higher (or equivalent to) the
 * length of string s, the function will do nothing.
 * 
 * If the length of the deleted portion from its starting position pos
 * extends past the end of the string, the remainder of the string
 * will be deleted.
 * 
 * Example: char foo[10] = "foobar";,                       
 * my_strdelete(foo, 3, 3) yields "foo".
 *
 * Example(2): char foo[10] = "foobar";
 * my_strdelete(foo, 0, 3) yields "bar".
 * 
 * Example(3): char foo[10] = "foobar";
 * my_strdelete(foo, 0, 34) yields "".
 */
void my_strdelete(char *s, int pos, int length)
{
  //LOCAL VARIABLE
  int i = 0; //starting position of the deleted elements on the string, also starting position of undeleted elements to be moved to
  int lengthstring; //length of the string
  int j = 0; //loop control expression, controlling the movements of undeleted elements to the front
  //COMPUTATIONS
  lengthstring = my_strlen(s);

  if ((length + pos) > lengthstring)
    {
      s[pos] = '\0';
    }
  else if ((length + pos) < lengthstring)
    {
      i = pos;
      for(j = (pos + length); j < lengthstring  ; j++) //moving the elements to the front, the limit is the length of the string so no segmentation fault would happen
	{
	  s[i] = s[j];
	  i++;
	}
      s[lengthstring - length] = '\0';
    }
}
