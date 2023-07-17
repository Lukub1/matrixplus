#include "s21_matrix_oop.h"

#include <gtest/gtest.h>

using namespace std;

TEST(ConstructorDestructor, Base) {
  S21Matrix a;
  EXPECT_TRUE(a.getRows() == 2);
  EXPECT_TRUE(a.getCols() == 2);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      EXPECT_TRUE(a(i + 1, y + 1) == 0);
    }
  }
}

TEST(ConstructorDestructor, Param) {
  S21Matrix a(50, 100);
  EXPECT_TRUE(a.getRows() == 50);
  EXPECT_TRUE(a.getCols() == 100);
  EXPECT_THROW(a(0, 0), std::out_of_range);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      EXPECT_TRUE(a(i + 1, y + 1) == 0);
    }
  }
}

TEST(ConstructorDestructor, CopyConstructor) {
  S21Matrix a(50, 100);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = rand() % 40;
    }
  }
  S21Matrix b(a);
  EXPECT_TRUE(a.getRows() == b.getRows());
  EXPECT_TRUE(a.getCols() == b.getCols());
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      EXPECT_TRUE(a(i + 1, y + 1) == b(i + 1, y + 1));
    }
  }
}

TEST(ConstructorDestructor, MoveConstructor) {
  S21Matrix a(50, 100);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i * y;
    }
  }
  S21Matrix b(std::move(a));
  EXPECT_TRUE(50 == b.getRows());
  EXPECT_TRUE(100 == b.getCols());
  EXPECT_TRUE(0 == a.getRows());
  EXPECT_TRUE(0 == a.getCols());
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      EXPECT_TRUE(b(i + 1, y + 1) == i * y);
    }
  }
}

TEST(ConstructorDestructor, Destructor) {
  S21Matrix a(50, 100);
  a.~S21Matrix();
  EXPECT_FALSE(a.getRows());
  EXPECT_FALSE(a.getCols());
}

TEST(AccessorMutator, GetRows) {
  S21Matrix a;
  EXPECT_EQ(a.getRows(), 2);
}

TEST(AccessorMutator, GetCols) {
  S21Matrix a(3, 5);
  EXPECT_EQ(a.getCols(), 5);
}

TEST(AccessorMutator, SetRows) {
  S21Matrix a(3, 5);
  a(2, 3) = 3.14;
  a.setRows(7);
  EXPECT_DOUBLE_EQ(a(2, 3), 3.14);
  EXPECT_DOUBLE_EQ(0, a(7, 5));
  EXPECT_EQ(a.getRows(), 7);
}

TEST(AccessorMutator, SetCols) {
  S21Matrix a(3, 5);
  a(2, 3) = 3.14;
  a.setCols(7);
  EXPECT_DOUBLE_EQ(a(2, 3), 3.14);
  EXPECT_DOUBLE_EQ(0, a(3, 7));
  EXPECT_EQ(a.getCols(), 7);
}

TEST(FuncMatrix, EqualsMatrix) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = rand() % 40;
    }
  }
  S21Matrix b(a);
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(FuncMatrix, SumMatrix) {
  S21Matrix a(3, 5);
  S21Matrix c;
  EXPECT_THROW(c.MulMatrix(a), std::out_of_range);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(3, 5);
  b.SumMatrix(a);
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(FuncMatrix, SubMatrix) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(3, 5);
  b.SubMatrix(a);
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      EXPECT_TRUE(b(i + 1, y + 1) == (-1 * (i + y)));
    }
  }
  S21Matrix c;
  EXPECT_THROW(c.MulMatrix(a), std::out_of_range);
}

TEST(FuncMatrix, MulNumMatrix) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  a.MulNumber(-3.14);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      EXPECT_TRUE(((i + y) * -3.14) == a(i + 1, y + 1));
    }
  }
}

TEST(FuncMatrix, MulMatrixMatrix) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  EXPECT_THROW(a.MulMatrix(a), std::out_of_range);
  S21Matrix b(5, 3);
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      b(i + 1, y + 1) = i + y;
    }
  }
  a.MulMatrix(b);
  S21Matrix result(3, 3);
  result(1, 1) = 30;
  result(1, 2) = 40;
  result(1, 3) = 50;
  result(2, 1) = 40;
  result(2, 2) = 55;
  result(2, 3) = 70;
  result(3, 1) = 50;
  result(3, 2) = 70;
  result(3, 3) = 90;
  EXPECT_TRUE(result.EqMatrix(a));
}

TEST(FuncMatrix, TransposeMatrix) {
  S21Matrix a(3, 5);
  S21Matrix b(5, 3);

  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
      b(y + 1, i + 1) = i + y;
    }
  }
  a = a.Transpose();
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      EXPECT_TRUE(a.EqMatrix(b));
    }
  }
}

TEST(FuncMatrix, CalcComplementsMatrix) {
  S21Matrix c(3, 5);
  EXPECT_THROW(c.CalcComplements(), std::out_of_range);
  S21Matrix a(3, 3);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(y + 1, i + 1) = i + y;
    }
  }
  S21Matrix result = a.CalcComplements();
  S21Matrix b(3, 3);
  b(1, 1) = -1;
  b(1, 2) = 2;
  b(1, 3) = -1;
  b(2, 1) = 2;
  b(2, 2) = -4;
  b(2, 3) = 2;
  b(3, 1) = -1;
  b(3, 2) = 2;
  b(3, 3) = -1;
  EXPECT_TRUE(b.EqMatrix(result));
}

TEST(FuncMatrix, DeterminantMatrix) {
  S21Matrix c(3, 5);
  EXPECT_THROW(c.Determinant(), std::out_of_range);
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(y + 1, i + 1) = i + y;
      if (y % 2) {
        b(y + 1, i + 1) = i + y;
      } else {
        b(y + 1, i + 1) = i * y + 1;
      }
    }
  }
  EXPECT_DOUBLE_EQ(a.Determinant(), 0);
  b.MulMatrix(a);
  b(3, 3) = 22;
  EXPECT_DOUBLE_EQ(b.Determinant(), 54);
}

TEST(FuncMatrix, InvertMatrix) {
  S21Matrix c(3, 5);
  EXPECT_THROW(c.InverseMatrix(), std::out_of_range);
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(y + 1, i + 1) = i + y;
      if (y % 2) {
        b(y + 1, i + 1) = i + y;
      } else {
        b(y + 1, i + 1) = i * y + 1;
      }
    }
  }
  EXPECT_THROW(a.InverseMatrix(), std::out_of_range);
  b.MulMatrix(a);
  b(3, 3) = 22;
  S21Matrix result(3, 3);
  result = b.InverseMatrix();
  b(1, 1) = -22.0 / 9.0;
  b(1, 2) = 11.0 / 9.0;
  b(1, 3) = -1.0 / 9.0;
  b(2, 1) = 14.0 / 9.0;
  b(2, 2) = -17.0 / 18.0;
  b(2, 3) = 2.0 / 9.0;
  b(3, 1) = -1.0 / 9.0;
  b(3, 2) = 2.0 / 9.0;
  b(3, 3) = -1.0 / 9.0;
  EXPECT_TRUE(b.EqMatrix(result));
}

TEST(OperatorMatrix, Asignment) {
  S21Matrix a(100, 100);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = rand() % 35;
    }
  }
  S21Matrix b;
  b = a;
  EXPECT_TRUE(b.EqMatrix(a));
}

TEST(OperatorMatrix, Plus) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(3, 5);
  b = a + b;
  EXPECT_TRUE(a.EqMatrix(b));
  S21Matrix c;
  EXPECT_THROW(c.MulMatrix(a), std::out_of_range);
}

TEST(OperatorMatrix, Minus) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(3, 5);
  b = b - a;
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      EXPECT_TRUE(b(i + 1, y + 1) == (-1 * (i + y)));
    }
  }
  S21Matrix c;
  EXPECT_THROW(c.MulMatrix(a), std::out_of_range);
}

TEST(OperatorMatrix, MultiplicationNumb) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b;
  b = a * -3.14;
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      EXPECT_TRUE(((i + y) * -3.14) == b(i + 1, y + 1));
    }
  }
}

TEST(OperatorMatrix, MultiplicationMatrix) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  EXPECT_THROW(a * a, std::out_of_range);
  S21Matrix b(5, 3);
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      b(i + 1, y + 1) = i + y;
    }
  }
  a = a * b;
  S21Matrix result(3, 3);
  result(1, 1) = 30;
  result(1, 2) = 40;
  result(1, 3) = 50;
  result(2, 1) = 40;
  result(2, 2) = 55;
  result(2, 3) = 70;
  result(3, 1) = 50;
  result(3, 2) = 70;
  result(3, 3) = 90;
  EXPECT_TRUE(result.EqMatrix(a));
}

TEST(OperatorMatrix, Equal) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = rand() % 40;
    }
  }
  S21Matrix b(a);
  EXPECT_TRUE(a == b);
}

TEST(OperatorMatrix, AdditionAssignment) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(3, 5);
  b += a;
  EXPECT_TRUE(a == b);
  S21Matrix c;
  EXPECT_THROW(c.MulMatrix(a), std::out_of_range);
}

TEST(OperatorMatrix, DifferenceAssignment) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(3, 5);
  b -= a;
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      EXPECT_TRUE(b(i + 1, y + 1) == (-1 * (i + y)));
    }
  }
  S21Matrix c;
  EXPECT_THROW(c.MulMatrix(a), std::out_of_range);
}

TEST(OperatorMatrix, MultiplicationAssignmentNumb) {
  S21Matrix a(3, 5);
  S21Matrix b(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
      b(i + 1, y + 1) = (i + y) * -3.14;
    }
  }
  a *= -3.14;
  EXPECT_TRUE(a == b);
}

TEST(OperatorMatrix, MultiplicationAssignmentMatrix) {
  S21Matrix a(3, 5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int y = 0; y < a.getCols(); y++) {
      a(i + 1, y + 1) = i + y;
    }
  }
  S21Matrix b(5, 3);
  for (int i = 0; i < b.getRows(); i++) {
    for (int y = 0; y < b.getCols(); y++) {
      b(i + 1, y + 1) = i + y;
    }
  }
  a *= b;
  S21Matrix result(3, 3);
  result(1, 1) = 30;
  result(1, 2) = 40;
  result(1, 3) = 50;
  result(2, 1) = 40;
  result(2, 2) = 55;
  result(2, 3) = 70;
  result(3, 1) = 50;
  result(3, 2) = 70;
  result(3, 3) = 90;
  EXPECT_TRUE(result == a);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
