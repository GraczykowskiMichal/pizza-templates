# pizza-templates \n
Project for Informatics at Warsaw University (Faculty of Mathematics, Informatics, Mechanics)  
Task:  
Create template ```template<typename... Kinds> struct Pizzeria``` which represents Pizzeria and provides the public structure ```template<typename Kind> struct make_pizza``` which represents 8-slices pizza of type ```Kind```. The pizza template should provide:  
1.public static method:  
  ```template<typename Kind> static constexpr size_t count();```  
  which returns amount of slices of type 'Kind';  
2.public static method:  
  ```static constexpr std::array<size_t, [N]> as_array();```  
  where [N] is the amount of pizza types available in the pizzeria, which returns an array of integers counting amount of      slices of each type provided while creating a pizzeria;  
3.public type ```c++ sliced_type which``` which represents pizza with each slice split into two;  
Moreover, create ```template<typename Pizza1, typename Pizza2> struct best_mix;``` which represents the best bizza which it is possible to make from types 'Pizza1' and 'Pizza2' (by taking any amount (even 0) of slices of 'Pizza1' and 'Pizza2'). The best_mix should compile only if 'Pizza1' and 'Pizza2' provide a 'yumminess' method, with the signature as below:  
```static constexpr [any arithmetic type] yumminess(size_t slices)```  
'yumminess' should return 0 for 0 slices.  
