#ifndef PIZZA_HH
#define PIZZA_HH

#include <type_traits>
#include <array>

//struktura reprezentująca pizzerię
template<typename... Kinds> struct Pizzeria {
private:
    
    //struktury pomocnicze do funkcji type_check() oraz if_no_repeats_check()
    template <typename...>
    struct is_one_of {
        static constexpr bool value = false;
    };
    
    template <typename F, typename S, typename... T>
    struct is_one_of<F, S, T...> {
        static constexpr bool value = std::is_same<F, S>::value ||
        is_one_of<F, T...>::value;
    };
    
    //sprawdza, czy podany typ jest jednym z wielu podanych typow
    template <typename F, typename... T> static constexpr bool type_check() {
        return is_one_of<F, T...>::value;
    }
    
    //sprawdza, czy zaden z podanych typow sie nie powtarza
    template <typename F, typename... T>
    static constexpr bool if_no_repeats_check() {
        return !is_one_of<F, T...>::value && !is_one_of<T...>::value;
    };
    
    
    
    //struktura reprezentująca pizzę
    template <size_t... pieces_count> struct Pizza {
    public:
        
        //funkcja zwracająca ilość kawałków danego typu w pizzy
        template<typename Kind> static constexpr size_t count() {
            return ((std::is_same<Kind, Kinds>::value * pieces_count) + ...);
        }
        
        //funkcja zwracająca tablicę ilości kawałków danego typu
        static constexpr std::array<size_t, sizeof...(Kinds)> as_array() {
            return {{count<Kinds>()...}};
        }
        
        //struktura reprezentująca podzieloną pizzę
        //(każdy kawałek podzielony na 2)
        typedef struct Pizza<2*pieces_count...> sliced_type;
        
        //typ reprezentujący pizzerię, z której pochodzi pizza
        using pizzeria_name = Pizzeria;
    };
    
    
    
    //zaprzyjaźnienie struktury best_mix w celu dzielenia struktury BestMix
    template<typename Pizza1, typename Pizza2> friend struct best_mix;
    
    //struktura zwracająca optymalną liczbę kawałków danych typów
    //dla Pizzy1 i Pizzy2 w operacji best_mix
    template <typename Pizza1, typename Pizza2> struct BestMix{
    private:
        
        //funkcja pomocnicza licząca optymalną liczbę kawałków danego typu
        template <typename Kind>
        static constexpr size_t best_mix_count(size_t current_amount,
                                               size_t best_amount,
                                               decltype(Kind::yumminess(0)) best_sum) {
            
            //sprawdzenie, czy typ implementuję metodę yumminess, która dla 0 zwraca wartość 0
            static_assert(Kind::yumminess(0) == 0, "No proper yumminess method!");
            
            //sprawdzenie, czy metoda yumminess zwraca typ arytmetyczny
            static_assert(std::is_arithmetic<decltype(Kind::yumminess(0))>::value,
                          "Yumminess does not return an arithmetic value!");
            
            size_t max_amount = Pizza1::template count<Kind>() +
            Pizza2::template count<Kind>();
            
            if (current_amount > max_amount) {
                return best_amount;
            }
            else {
                auto current_sum = Kind::yumminess(current_amount);
                if (current_sum > best_sum)
                    return best_mix_count<Kind>(current_amount + 1,
                                                current_amount,
                                                current_sum);
                else
                    return best_mix_count<Kind>(current_amount + 1,
                                                best_amount,
                                                best_sum);
            }
        }
        
    public:
        
        //typ przechowujący pizzę o optymalnej liczbie kawałków
        //każdego typu w operacji best_mix
        using type = Pizza<best_mix_count<Kinds>(0, 0, 0)...>;
    };
    
public:
    
    //sprawdzenie poprawności deklaracji pizzerii
    static_assert(if_no_repeats_check<Kinds...>(),
                  "The same pizza twice in the menu? It doesn't make sense!");
    
    //struktura tworząca podstawową pizzę
    template<typename Kind> struct make_pizza {
        
        //sprawdzenie poprawności argumentów tworzenia pizzy
        static_assert(type_check<Kind, Kinds...>(),
                      "You cannot create pizza which is not listed in the menu.");
        
        //typ przechowujący podstawową pizzę
        typedef struct Pizza<std::is_same<Kind, Kinds>::value * 8 ...> type;
    };
};



//struktura reprezentująca best_mix
template<typename Pizza1, typename Pizza2>
struct best_mix {
    
    //sprawdzenie poprawności typów dla operacji best_mix
    static_assert(std::is_same<typename Pizza1::pizzeria_name,
                  typename Pizza2::pizzeria_name>::value,
                  "Pizzas for best_mix must come from the same pizzeria!");
    
    //typ przechowujący pizzę o optymalnej liczbie kawałków każdego typu
    using type = typename Pizza1::pizzeria_name::template BestMix<Pizza1, Pizza2>::type;
};

#endif /* PIZZA_HH */
