# pizza-templates \n
Project for Informatics at Warsaw University (Faculty of Mathematics, Informatics, Mechanics)__
Task:  
Create template ```template<typename... Kinds> struct Pizzeria``` which represents Pizzeria and provides the public structure ```template<typename Kind> struct make_pizza``` which represents 8-slices pizza of type ```Kind```. The pizza template should provide:__
1.public static method:__
  ```template<typename Kind> static constexpr size_t count();```__
  which returns amount of slices of type 'Kind';__
2.public static method:__
  ```static constexpr std::array<size_t, [N]> as_array();```__
  where [N] is the amount of pizza types available in the pizzeria, which returns an array of integers counting amount of      slices of each type provided while creating a pizzeria;__
3.public type ```c++ sliced_type which``` represents pizza with each slice split into two;__
