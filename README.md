# lstd

My own implementation of some standard library data structures in C++ (Luis' std) to develop a better understanding of modern C++ features and the actual std

## Design philosophy

These are the rules I use to develop this library: 

1. **Minimalist design**: We should use the least amount of reasonable code to implement the library. All code we make should be easily mapped to a feature

2. **Minimum reliance on std**:  The point of this exercise is to understand and implement the std from first principles, in a more easy-to-reason manner. So by avoiding the std we understand: 
   
   1. What is the most needed from the std
   
   2. What is easy to replace, what is not
   
   3. We learn the ergonomics of the library by actually using it!

3. **Stay familiar, don’t obsess**: Keeping the same interface of the std char by char is not required, but I will try to keep it as similar as possible. The idea being to understand why some things in the STD are the way they are, and see if I achieve the same conclusions or if I have a different take 

4. **Minimum build system**: In the spirit of rule 1, the build system should be as simple as possible, so that it's easy to develop and include in future projects
