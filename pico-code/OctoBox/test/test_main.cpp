#include "unity.h"
#include "main.cpp"

void test_mutex(void){
  // Simulate acquiring the mutex
  settingsFileLock = true;

  // Assert that the mutex is locked
  TEST_ASSERT_TRUE(settingsFileLock);

  // Simulate releasing the mutex
  settingsFileLock = false;

  // Assert that the mutex is unlocked
  TEST_ASSERT_FALSE(settingsFileLock);
}

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

int main(void) {
  Serial.begin(115200);
  UNITY_BEGIN();
  RUN_TEST(test_mutex);
  return UNITY_END();
}
