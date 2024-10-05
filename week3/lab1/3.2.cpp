#include <random>
#include <fstream>
#include <iostream>

struct DiceLayout {
    virtual ~DiceLayout() = default;
    virtual unsigned roll() = 0;
};

class Dice : public DiceLayout {
public:
    Dice(unsigned max_value, unsigned seed_value)
        : max_value(max_value), distribution(1, max_value), engine(seed_value) {}

    unsigned roll() override {
        return distribution(engine);
    }

private:
    unsigned max_value;
    std::uniform_int_distribution<unsigned> distribution;
    std::default_random_engine engine;
};

class PenaltyDice : public DiceLayout {
public:
    explicit PenaltyDice(DiceLayout& base_dice)
        : base_dice(base_dice) {}

    unsigned roll() override {
        auto first_roll = base_dice.roll();
        auto second_roll = base_dice.roll();
        return std::min(first_roll, second_roll);
    }

private:
    DiceLayout& base_dice;
};

class BonusDice : public DiceLayout {
public:
    explicit BonusDice(DiceLayout& base_dice)
        : base_dice(base_dice) {}

    unsigned roll() override {
        auto first_roll = base_dice.roll();
        auto second_roll = base_dice.roll();
        return std::max(first_roll, second_roll);
    }

private:
    DiceLayout& base_dice;
};

class DoubleDice : public DiceLayout {
public:
    explicit DoubleDice(DiceLayout& base_dice)
        : penalty_dice(base_dice), bonus_dice(base_dice) {}

    unsigned roll() override {
        return (penalty_dice.roll() + bonus_dice.roll()) / 2;
    }

private:
    PenaltyDice penalty_dice;
    BonusDice bonus_dice;
};

double calculate_expected_value(DiceLayout& dice, unsigned rolls = 1) {
    unsigned long long total = 0;
    for (unsigned i = 0; i < rolls; ++i) {
        total += dice.roll();
    }
    return static_cast<double>(total) / rolls;
}

double calculate_value_probability(DiceLayout& dice, unsigned target_value, unsigned rolls = 1) {
    unsigned hits = 0;
    for (unsigned i = 0; i < rolls; ++i) {
        if (dice.roll() == target_value) {
            ++hits;
        }
    }
    return static_cast<double>(hits) / rolls;
}

int main() {
    unsigned max_value = 100;
    unsigned num_rolls = 1000;

    Dice base_dice(max_value, 1123);
    DoubleDice double_dice(base_dice);

    std::cout << "Expected value: " << calculate_expected_value(double_dice, num_rolls) << std::endl;

    std::ofstream data_file("third.csv");
    data_file << "Target\tDouble" << std::endl;

    for (unsigned target = 1; target < max_value; ++target) {
        data_file << target << "\t" << calculate_value_probability(double_dice, target, num_rolls) << std::endl;
    }

    data_file.close();
    return 0;
}
