#include <cstdio>
#include <random>
enum Allocation { hidden, revealed, mine };

struct Tile {
  Allocation status = hidden;
  bool is_mine_ = false;
  int mine_Arround_ = 0;
};

class SpielFeld : public Tile {
 private:
  const int rows_ = 12;
  int colonn_ = 12;

  Tile feld_[12][12];

 public:
  int verbleibendeFelder_;
  int score_ = 0;
  SpielFeld() {}

  void initialize(int n) {
    verbleibendeFelder_ = rows_ * colonn_ - n;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, colonn_);
    while (n > 0) {
      int x = dist(rd);
      int y = dist(rd);
      if (!feld_[x][y].is_mine_) {
        feld_[x][y].is_mine_ = true;
        n--;
      }
    }

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < colonn_; ++j) {
        feld_[i][j].status = hidden;
        feld_[i][j].mine_Arround_ = mine_Neighbour(i, j);
      }
    }
  }

  int mine_Neighbour(int x, int y) {
    if (!feld_[x][y].is_mine_) {
      int count = 0;
      if (x == 0 && y == 0) {
        for (int i = 0; i < 2; ++i) {
          for (int j = 0; j < 2; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x == 0 && y == colonn_ - 1) {
        for (int i = 0; i < 2; ++i) {
          for (int j = y - 1; j < y + 1; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x == 0 && y < colonn_ - 1) {
        for (int i = 0; i < 2; ++i) {
          for (int j = y - 1; j < y + 2; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x == rows_ - 1 && y == 0) {
        for (int i = x - 1; i < x + 1; ++i) {
          for (int j = 0; j < 2; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x == rows_ - 1 && y == colonn_ - 1) {
        for (int i = x - 1; i < x + 1; ++i) {
          for (int j = y - 1; j < y + 1; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x == rows_ - 1 && y <= colonn_ - 2 && y > 0) {
        for (int i = x - 1; i < x + 1; ++i) {
          for (int j = y - 1; j < y + 2; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x >= 1 && y == 0 && x < rows_ - 1) {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y; j <= y + 1; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
      if (x >= 1 && y == colonn_ - 1 && x < rows_ - 1) {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y - 1; j <= y; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      } else {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y - 1; j <= y + 1; ++j) {
            if (feld_[i][j].is_mine_) {
              count++;
            }
          }
        }
        return count;
      }
    } else
      return 0;
  }

  void display(bool b) {
    int k = 00;
    printf("\n");
    printf("  Verbleibende verdeckten Felder: %i\n", verbleibendeFelder_);
    for (int i = 0; i < rows_; ++i) {
      if (k < 10) printf("0");
      printf("%i| ", k);
      for (int j = 0; j < colonn_; ++j) {
        Allocation fall = feld_[i][j].status;
        switch (fall) {
          case hidden:
            if (b && feld_[i][j].is_mine_) {
              printf(" X ");
            } else {
              printf(" * ");
            }
            break;
          case revealed:

            if (feld_[i][j].is_mine_) {
              printf(" X ");
            } else {
              if (feld_[i][j].mine_Arround_ == 0) {
                printf(" . ");
              } else {
                printf(" %i ", feld_[i][j].mine_Arround_);
              }
            }
            break;
          case mine:

            if (b)
              printf(" X ");
            else
              printf(" * ");
            break;
        }
      }
      printf(" \n");
      k++;
    }
    printf("     -----------------------------------\n");
    printf("   ");
    for (int k = 0; k < colonn_; ++k) {
      if (k < 10) {
        printf(" 0%i", k);
      } else {
        printf(" %i", k);
      }
    }
    printf("\n");
    printf("\n");
    printf("Dein Score ist : %i\n", score_);
    printf("\n");
  }

  bool eingabe() {
    int x, y;
    do {
      printf(" Geben Sie die i-te Koordinate: \n");
      scanf(" %i", &x);
      printf(" Geben Sie die j-te Koordinate: \n");
      scanf(" %i", &y);
    } while (x < 0 || y < 0 || x > 11 || y > 11 ||
             feld_[x][y].status == revealed);

    if (feld_[x][y].is_mine_) {
      score_ -= (100 + 10 * mine_Neighbour(x, y));
      if (score_ < 0)
        display(true);
      else {
        feld_[x][y].status = revealed;
        verbleibendeFelder_--;
        display(false);
      }
      return true;
    } else {
      feld_[x][y].status = revealed;
      verbleibendeFelder_--;
      checkNeighbours();
      score_ += 50 * mine_Neighbour(x, y);
      display(false);
      return false;
    }
  }

  bool revealedEmptyNeighbour(int x, int y) {
    if (!feld_[x][y].is_mine_ && feld_[x][y].status != revealed) {
      if (x == 0 && y == 0) {
        for (int i = 0; i < 2; ++i) {
          for (int j = 0; j < 2; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].mine_Arround_ == 0 &&
                  feld_[i][j].status == revealed) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x == 0 && y == colonn_ - 1) {
        for (int i = 0; i < 2; ++i) {
          for (int j = y - 1; j < y + 1; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x == 0 && y < colonn_ - 1) {
        for (int i = 0; i < 2; ++i) {
          for (int j = y - 1; j < y + 2; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x == rows_ - 1 && y == 0) {
        for (int i = x - 1; i < x + 1; ++i) {
          for (int j = 0; j < 2; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x == rows_ - 1 && y == colonn_ - 1) {
        for (int i = x - 1; i < x + 1; ++i) {
          for (int j = y - 1; j < y + 1; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x == rows_ - 1 && y <= colonn_ - 2 && y > 0) {
        for (int i = x - 1; i < x + 1; ++i) {
          for (int j = y - 1; j < y + 2; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x >= 1 && y == 0 && x < rows_ - 1) {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y; j <= y + 1; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
      if (x >= 1 && y == colonn_ - 1 && x < rows_ - 1) {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y - 1; j <= y; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      } else {
        for (int i = x - 1; i <= x + 1; ++i) {
          for (int j = y - 1; j <= y + 1; ++j) {
            if (i != x && j != y) {
              if (feld_[i][j].status == revealed &&
                  feld_[i][j].mine_Arround_ == 0) {
                feld_[x][y].status = revealed;
                // verbleibendeFelder_--;
                return true;
              }
            }
          }
        }
        return false;
      }
    } else
      return false;
  }

  bool checkNeighbours() {
    int count = 0;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < colonn_; ++j) {
        if (feld_[i][j].status == hidden) {
          bool check = revealedEmptyNeighbour(i, j);
          if (check) {
            feld_[i][j].status = revealed;
            verbleibendeFelder_--;
            count++;
          }
        }
      }
    }
    if (0 < count)
      return true;
    else
      return false;
  }
};
