#include "ActivatedAbility.h"
#include <iostream>

ActivatedAbility::ActivatedAbility(int cost, std::string description, std::unique_ptr<Effect> effect)
    : Ability(std::move(effect), std::move(description)), cost(cost) {}

void ActivatedAbility::useEffect(Minion* target) {
    std::cout << "ActivatedAbility: " << description << std::endl;

    if (effect) {
        // Set target if one is required
        if (effect->supportsTarget()) {
            effect->setTarget(target);
        }
        effect->apply();
    } else {
        std::cerr << "Error: Ability has no effect" << std::endl;
    }
}

int ActivatedAbility::getActivationCost() const {
    return cost;
}

std::unique_ptr<Effect> ActivatedAbility::cloneEffect() const {
    return effect ? effect->clone() : nullptr;
}

std::unique_ptr<Ability> ActivatedAbility::clone() const {
    return std::make_unique<ActivatedAbility>(cost, description, cloneEffect());
}

