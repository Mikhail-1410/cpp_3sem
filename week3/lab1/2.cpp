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
        auto first = base_dice.roll();
        auto second = base_dice.roll();
        return std::min(first, second);
    }

private:
    DiceLayout& base_dice;
};

class BonusDice : public DiceLayout {
public:
    explicit BonusDice(DiceLayout& base_dice)
        : base_dice(base_dice) {}

    unsigned roll() override {
        auto first = base_dice.roll();
        auto second = base_dice.roll();
        return std::max(first, second);
    }

private:
    DiceLayout& base_dice;
};

class ThreeDicePool : public DiceLayout {
public:
    ThreeDicePool(DiceLayout& dice1, DiceLayout& dice2, DiceLayout& dice3)
        : dice1(dice1), dice2(dice2), dice3(dice3) {}

    unsigned roll() override {
        return dice1.roll() + dice2.roll() + dice3.roll();
    }

private:
    DiceLayout& dice1;
    DiceLayout& dice2;
    DiceLayout& dice3;
};

double calculate_value_probability(DiceLayout& dice, unsigned target_value, unsigned rolls = 1) {
    unsigned hit_count = 0;
    for (unsigned i = 0; i < rolls; ++i) {
        if (dice.roll() == target_value) {
            ++hit_count;
        }
    }
    return static_cast<double>(hit_count) / rolls;
}

double calculate_expected_value(DiceLayout& dice, unsigned rolls = 1) {
    unsigned long long total_value = 0;
    for (unsigned i = 0; i < rolls; ++i) {
        total_value += dice.roll();
    }
    return static_cast<double>(total_value) / rolls;
}

int main() {
    unsigned max_value = 100;
    unsigned pool_max_value = 6;
    unsigned num_rolls = 1000000;

    Dice alpha(max_value, 12414);
    Dice beta(pool_max_value, 12423414);
    Dice gamma(pool_max_value, 122414);
    Dice theta(pool_max_value, 213123);

    ThreeDicePool dice_pool(beta, gamma, theta);
    PenaltyDice penalty(alpha);
    BonusDice bonus(alpha);

    std::cout << calculate_expected_value(alpha, num_rolls) << " "
              << calculate_expected_value(penalty, num_rolls) << " "
              << calculate_expected_value(bonus, num_rolls) << std::endl;

    std::ofstream data_file("second.csv");
    data_file << "Target\tStandart\tThreeDice\tPenalty\tBonus" << std::endl;

    for (unsigned target = 1; target < max_value; ++target) {
        data_file << target << "\t"
                  << calculate_value_probability(alpha, target, num_rolls) << "\t"
                  << calculate_value_probability(dice_pool, target, num_rolls) << "\t"
                  << calculate_value_probability(penalty, target, num_rolls) << "\t"
                  << calculate_value_probability(bonus, target, num_rolls) << std::endl;
    }

    data_file.close();
    return 0;
}
