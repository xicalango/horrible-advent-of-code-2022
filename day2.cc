#include <iostream>
#include <limits>

#include "list.hpp"
#include "value.hpp"
#include "print.hpp"
#include "control.hpp"

#include "input/day2-guide.hpp"

// #region symbols

// #region definition

struct Rock;
struct Paper;
struct Scissors;

struct Rock {
    typedef Rock Draw;
    typedef Paper Win;
    typedef Scissors Lost;
};

struct Paper {
    typedef Rock Lost;
    typedef Paper Draw;
    typedef Scissors Win;
};

struct Scissors {
    typedef Rock Win;
    typedef Paper Lost;
    typedef Scissors Draw;
};

// #endregion

// #region scores

template<typename Sign>
struct SignScore;

template<>
struct SignScore<Rock> {
    static const int ResultValue = 1;
};

template<>
struct SignScore<Paper> {
    static const int ResultValue = 2;
};

template<>
struct SignScore<Scissors> {
    static const int ResultValue = 3;
};

// #endregion

// #endregion

// #region scoring

static const int ScoreLost = 0;
static const int ScoreDraw = 3;
static const int ScoreWin = 6;

template<typename Opponent, typename Me>
struct Score;

// Op: Rock

template<>
struct Score<Rock, Rock> {
    static const int ResultValue = ScoreDraw + SignScore<Rock>::ResultValue;
};

template<>
struct Score<Rock, Paper> {
    static const int ResultValue = ScoreWin + SignScore<Paper>::ResultValue;
};

template<>
struct Score<Rock, Scissors> {
    static const int ResultValue = ScoreLost + SignScore<Scissors>::ResultValue;
};

// Op: Paper

template<>
struct Score<Paper, Rock> {
    static const int ResultValue = ScoreLost + SignScore<Rock>::ResultValue;
};

template<>
struct Score<Paper, Paper> {
    static const int ResultValue = ScoreDraw + SignScore<Paper>::ResultValue;
};

template<>
struct Score<Paper, Scissors> {
    static const int ResultValue = ScoreWin + SignScore<Scissors>::ResultValue;
};

// Op: Scissors

template<>
struct Score<Scissors, Rock> {
    static const int ResultValue = ScoreWin + SignScore<Rock>::ResultValue;
};

template<>
struct Score<Scissors, Paper> {
    static const int ResultValue = ScoreLost + SignScore<Paper>::ResultValue;
};

template<>
struct Score<Scissors, Scissors> {
    static const int ResultValue = ScoreDraw + SignScore<Scissors>::ResultValue;
};

// #endregion

// #region converters

template<char Opponent>
struct ConvertOpponent;

template<>
struct ConvertOpponent<'A'> {
    typedef Rock Result;
};

template<>
struct ConvertOpponent<'B'> {
    typedef Paper Result;
};

template<>
struct ConvertOpponent<'C'> {
    typedef Scissors Result;
};

template<char Me>
struct ConvertMe;

template<>
struct ConvertMe<'X'> {
    typedef Rock Result;
};

template<>
struct ConvertMe<'Y'> {
    typedef Paper Result;
};

template<>
struct ConvertMe<'Z'> {
    typedef Scissors Result;
};

// #endregion

// #region scoring

template<char Opponent, char Me>
struct ScoreSimple {
    typedef typename ConvertOpponent<Opponent>::Result OpponentResult;
    typedef typename ConvertMe<Me>::Result MeResult;

    static const int Value = Score<OpponentResult, MeResult>::ResultValue;

};

template<typename Opponent, char Me>
struct GetMove;

template<typename Opponent>
struct GetMove<Opponent, 'Y'> {
    typedef typename Opponent::Draw Result;
};

template<typename Opponent>
struct GetMove<Opponent, 'X'> {
    typedef typename Opponent::Lost Result;
};

template<typename Opponent>
struct GetMove<Opponent, 'Z'> {
    typedef typename Opponent::Win Result;
};

template<char Opponent, char Me>
struct ScoreAdvanced {
    typedef typename ConvertOpponent<Opponent>::Result OpponentResult;
    typedef typename GetMove<OpponentResult, Me>::Result MeResult;

    static const int Value = Score<OpponentResult, MeResult>::ResultValue;
};

// #endregion

template<typename T>
struct ConvSimple;

template<char A, char B>
struct ConvSimple<C_TUPLE<A, B>> {
    typedef ScoreSimple<A, B> Result;
};

template<typename T>
struct ConvAdvanced;

template<char A, char B>
struct ConvAdvanced<C_TUPLE<A, B>> {
    typedef ScoreAdvanced<A, B> Result;
};

template<char A, char B>
struct PRINT<ScoreSimple<A, B>> {
    static void print() {
        std::cout << "ScoreSimple(" << A << ',' << B << ") = " << ScoreSimple<A, B>::Value << std::endl;
    }
};

template<char A, char B>
struct PRINT<ScoreAdvanced<A, B>> {
    static void print() {
        std::cout << "ScoreAdvanced(" << A << ',' << B << ") = " << ScoreSimple<A, B>::Value << std::endl;
    }
};

typedef L<C_TUPLE<'A', 'Y'>,
        L<C_TUPLE<'B', 'X'>,
        L<C_TUPLE<'C', 'Z'>,
        LE
        >>>
        ExampleScores;

int main(void) {

    PRINT<ExampleScores>::print();

    typedef ConvSimple<ExampleScores::Head>::Result FirstConv;

    PRINT<FirstConv>::print();

    typedef MAP<ExampleScores, ConvSimple>::Result Mapped;

    PRINT<Mapped>::print();

    typedef SUM_INT<Mapped>::Result ExampleResult;

    PRINT<ExampleResult>::print();

    {   
        typedef MAP<Day2::MOVES, ConvSimple>::Result MappedMoves;
        typedef SUM_INT<MappedMoves>::Result Day2Result;
        std::cout << "simple score: ";
        PRINT<Day2Result>::print();
    }

    {   
        typedef MAP<Day2::MOVES, ConvAdvanced>::Result MappedMoves;
        typedef SUM_INT<MappedMoves>::Result Day2Result;
        std::cout << "advanced score: ";
        PRINT<Day2Result>::print();
    }
}
