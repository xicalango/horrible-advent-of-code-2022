#include <iostream>
#include <limits>
#include <cmath>

#include "list.hpp"
#include "value.hpp"
#include "print.hpp"
#include "control.hpp"

#include "input/day10_example.hpp"
#include "input/day10.hpp"

struct Noop;

template<int V>
struct AddX;

template<typename Instruction, typename Register>
struct ExecInstruction;

template<typename Register>
struct ExecInstruction<Noop, Register> {
  static const int UpdatedRegisterValue = Register::Value;
  typedef I<UpdatedRegisterValue> UpdatedRegister;

  typedef L<Register, LE> Result;
};

template<int V, typename Register>
struct ExecInstruction<AddX<V>, Register> {
  static const int UpdatedRegisterValue = Register::Value + V;
  typedef I<UpdatedRegisterValue> UpdatedRegister;

  typedef L<Register, L<UpdatedRegister, LE>> Result;
};


template<typename RegisterState, typename Instruction>
struct SimulateInstruction {
  typedef ExecInstruction<Instruction, RegisterState> ExecutedInstruction;
  typedef typename ExecutedInstruction::UpdatedRegister NewState;
  typedef typename ExecutedInstruction::Result Result;
};


template<typename RegisterState, typename InstructionList>
struct Simulate {
  typedef typename InstructionList::Head Instruction;
  typedef SimulateInstruction<RegisterState, Instruction> Simulation;

  typedef Simulate<typename Simulation::NewState, typename InstructionList::Tail> SimulationContinued;

  typedef typename CONCAT<typename Simulation::Result, typename SimulationContinued::Result>::Result Result;  

};

template<typename RegisterState>
struct Simulate<RegisterState, LE> {
  typedef LE Result;
};

template<typename InstructionList>
struct SimulateStart {
  typedef L<I<1>, typename Simulate<I<1>, InstructionList>::Result> Result;
};

template<typename T>
struct ParseInput;

template<>
struct ParseInput<C<'N'>> {
  typedef Noop Result;
};

template<int i>
struct ParseInput<I<i>> {
  typedef AddX<i> Result;
};

template<typename T>
struct FilterRelevantLine {
  static const bool ResultValue = T::A::Value >= 20 && (T::A::Value - 20) % 40 == 0;
};

template<>
struct PRINT<Noop> {
  static void print() {
    std::cout << "NOOP" << std::endl;
  }
};

template<int x>
struct PRINT<AddX<x>> {
  static void print() {
    std::cout << "AddX " << x << std::endl;
  }
};

template<typename T>
struct CalcScore {
  typedef I<T::A::Value * T::B::Value> Result;
};


// #region task2

template<typename T>
struct Draw;

template<int index, int regValue>
struct Draw<TUPLE<I<index>, I<regValue>>> {
  typedef typename IF<
    /*when*/ (std::abs(((index-1) % 40) - regValue) <= 1),
    /*then*/ C<'#'>,
    /*else*/ C<' '>
  >::Result DrawChar;

  typedef typename IF<
    /*when*/ (index % 40 == 0),
    /*then*/ C<'\n'>,
    /*else*/ C<'\0'>
  >::Result Endline;

  typedef TUPLE<DrawChar, Endline> Result;
};

template<typename T>
struct PrintScreen;

template<char drawChar, char endLine>
struct PrintScreen<TUPLE<C<drawChar>, C<endLine>>> {
  static void run() {
    std::cout << drawChar << endLine;
  }
};


// #endregion

typedef
  L<Noop,
  L<AddX<3>,
  L<AddX<-5>,
  LE
  >>>
  EXAMPLE_INPUT1;


int main(void) {
  {
    typedef typename SimulateStart<EXAMPLE_INPUT1>::Result SimulationResult;
    //PRINT<SimulationResult>::print();

    typedef typename ZIP_WITH_INDEX<SimulationResult, I<1>>::Result Zipped;
    //PRINT<Zipped>::print();
  }

  {
    typedef typename MAP<Day10Input::EXAMPLE1, ParseInput>::Result MappedInput;
    //PRINT<MappedInput>::print();

    typedef typename SimulateStart<MappedInput>::Result SimulationResult;
    //PRINT<SimulationResult>::print();

    typedef typename ZIP_WITH_INDEX<SimulationResult, I<1>>::Result Zipped;
    //PRINT<Zipped>::print();
    //std::cout << std::endl;

    typedef typename FILTER<Zipped, FilterRelevantLine>::Result Filtered;
    // PRINT<Filtered>::print();
    // std::cout << std::endl;

    typedef typename MAP<Filtered, CalcScore>::Result Scores;
    // PRINT<Scores>::print();

    int result = SUM_INT<Scores>::ResultValue;
    std::cout << "result: " << result << std::endl;

    typedef typename MAP<Zipped, Draw>::Result Screen;
    RUN<Screen, PrintScreen>::run();
    std::cout << std::endl;
  }

  {
    typedef typename MAP<Day10Input::INPUT, ParseInput>::Result MappedInput;
    //PRINT<MappedInput>::print();

    typedef typename SimulateStart<MappedInput>::Result SimulationResult;
    //PRINT<SimulationResult>::print();

    typedef typename ZIP_WITH_INDEX<SimulationResult, I<1>>::Result Zipped;
    //PRINT<Zipped>::print();
    //std::cout << std::endl;

    typedef typename FILTER<Zipped, FilterRelevantLine>::Result Filtered;
    // PRINT<Filtered>::print();

    // std::cout << std::endl;

    typedef typename MAP<Filtered, CalcScore>::Result Scores;
    // PRINT<Scores>::print();

    int result = SUM_INT<Scores>::ResultValue;
    std::cout << "result: " << result << std::endl;
  
    typedef typename MAP<Zipped, Draw>::Result Screen;
    RUN<Screen, PrintScreen>::run();
    std::cout << std::endl;
  }
}
