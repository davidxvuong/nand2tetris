# Some notes about the HACK Assembler

For more information about this project, please refer to the [nand2tetris](http://nand2tetris.org) website.

I chose to implement the assembler in C. Why did I choose this language? Well, for one thing, after coming off my final term in university, C was my most frequently used language, and as a result it was the language that I gravitated to.

There were a lot of string manipulations that needed to be done in this project, and C just wasn't built for that. Furthermore, it did not have any standard data structures (List, HashMap, etc.). As a result, I spent some more of my time implementing these and making sure that my string manipulations actually do what I want to do. If I were to implement this again, I would definitely do it in a higher level language such as Java. That way I wouldn't have to waste time wrestling with the language to implement the data structures that I need.

Midway through my development, I came across a [forum post](http://nand2tetris-questions-and-answers-forum.32033.n3.nabble.com/Assembler-implementation-td3520996.html#a4026045) suggesting that I should use a hash table called [uthash](http://troydhanson.github.io/uthash/index.html). I could've used this when implementing the symbol table and the instruction bit lookup. But I was too deep into my implementation that I don't want to mess up my work. I will remember this for my future projects.

While this assembler works, it is really slow when you encounter a HACK program that is ~20,000 lines long (for example, the Pong program). Some work will be needed to parallelize this program so that it does not take ~10 seconds to complete the translation from HACK assembly to HACK machine language (this sounds like a project that [ECE 459](https://uwflow.com/course/ece459) can do :) ). 