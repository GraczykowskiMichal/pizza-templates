# pizza-templates
Project for Informatics at Warsaw University (Faculty of Mathematics, Informatics, Mechanics)
Task:
Create template "template<typename... Kinds> struct Pizzeria" which represents Pizzeria and provides the public structure "template<typename Kind> struct make_pizza" which represents 8-slices pizza of type 'Kind'. The pizza template should provide:
1)public static method:
  template<typename Kind> static constexpr size_t count();
  which returns amount of slices of type 'Kind'
2)public static method:
  static constexpr std::array<size_t, [N]> as_array();
  where [N] is the amount of pizza types available in the pizzeria, which returns an array of integers counting amount of      slices of each type provided while creating a pizzeria.
3)public type sliced_type which represents pizza with each slice split into two.
