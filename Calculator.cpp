
#include <string>
#include <cstdint>
#include<sstream>
#include <iostream>

template <class T>

struct Stack {

  size_t size{};

  int64_t stack_p{-1};

  T* stack = nullptr ;


};


template <class T>

void init(Stack<T>& st, size_t size) {

  st.size = size;

  st.stack = new T[size];
  st.stack_p = -1;

}


template <class T>

void clear(Stack <T>& st) {

  st.stack_p = 0;


}


template <class T>

bool empty(Stack <T>& st) {

  return (st.stack_p == -1);

  

}


template <class T>

T top(Stack <T>& st) {

  return st.stack[st.stack_p];

}


template <class T>

void push(Stack<T>& st, T var) {

  st.stack[++st.stack_p] = var;



}


template <class T>

T pop(Stack <T>& st) {

  return (st.stack[st.stack_p--]);

}


int64_t expa(int64_t num, int64_t degree) {

  int64_t ans{ num };

  for (int16_t i{ 1 }; i < degree; ++i) {

    num *= ans;

  }

  return num;

}


int32_t Math(int64_t a, int64_t b,const char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
         case '/': return a / b;
        case '^': return expa(a, b);
        default: return 0;
    }
}

int16_t VIP(char sign){
  if(sign == '+' || sign == '-'){return 1;}
  if(sign == '*' || sign == '/')return 2;
  if (sign == '^') return 3;
  return 0;
}

int main()

{

  std::string expres = "2 * 2 + 3 * ( 4 - 2 ) ^ 2";

  Stack<char> msigns;
  init(msigns, expres.size());

  Stack<int32_t> dig;
  init(dig, expres.size());


  std::stringstream ss(expres);
  std::string buff = "";

  while (ss >> buff) {

    if (isdigit(buff[0])){
      push(dig , std::stoi(buff));
    }
    else if (buff == "(") {
            push(msigns, '(');
        }

        else if (buff == ")") {
            while (!empty(msigns) && top(msigns) != '(') {
                double val2 = pop(dig);
                double val1 = pop(dig);
                char op = pop(msigns);
                push(dig, Math(val1, val2, op));
            }
            if (!empty(msigns)) pop(msigns);
        }

        else {
            char current_op = buff[0];
            while (!empty(msigns) && VIP(top(msigns)) >= VIP(current_op)) {
                int64_t val2 = pop(dig);
                int64_t val1 = pop(dig);
                char op = pop(msigns);
                push(dig, Math(val1, val2, op));
            }
            push(msigns, current_op);
        }
    }

    while (!empty(msigns)) {
        double val2 = pop(dig);
        double val1 = pop(dig);
        char op = pop(msigns);
        push(dig, Math(val1, val2, op));
    }

    std::cout << "Answer = " << pop(dig) << '\n';

    clear(msigns);
    clear(dig);
    return 0;


}
