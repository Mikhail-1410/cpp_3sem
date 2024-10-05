#include <random>
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

double calculate_expected_value(DiceLayout& dice, unsigned num_rolls = 1) {
    unsigned long long total = 0;
    for (unsigned i = 0; i < num_rolls; ++i) {
        total += dice.roll();
    }
    return static_cast<double>(total) / num_rolls;
}

int main() {
    unsigned max_val = 6;
    unsigned num_trials = 1000000;

    Dice first_dice(max_val, 12414);
    Dice second_dice(max_val, 12423414);
    Dice third_dice(max_val, 122414);

    ThreeDicePool dice_pool(first_dice, second_dice, third_dice);

    std::cout << "Single Dice Roll: " << first_dice.roll() << '\n';
    std::cout << "Three Dice Pool Roll: " << dice_pool.roll() << '\n';

    std::cout << "Expected Value for Single Dice: " << calculate_expected_value(first_dice, num_trials) << '\n';
    std::cout << "Expected Value for Three Dice Pool: " << calculate_expected_value(dice_pool, num_trials) << '\n';

    return 0;
}
