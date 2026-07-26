#pragma once
#include <vector>

constexpr int NUM_BARS = 32;
constexpr float BAR_WIDTH = 0.04f;
constexpr float BAR_GAP = 0.02f;
constexpr float BASELINE = -1.0f;
constexpr float MAX_TOP = 0.85f;     // top of screen a bar can reach at full height
constexpr float MIN_HEIGHT = 0.02f;

std::vector<float> generateVertices();

void updateBarHeights(std::vector<float>& vertices, const std::vector<float>& barHeights);