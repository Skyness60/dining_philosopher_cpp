
# Variables principales
CPP = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -MMD -MP -Iinclude
LDFLAGS =
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
SOURCES = $(shell find $(SRC_DIR) -name '*.cc')
OBJECTS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS = $(OBJECTS:.o=.d)
NAME = philo
TARGET = $(BIN_DIR)/$(NAME)


# Cible principale
all: $(TARGET)

# Lien final
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CPP) $(LDFLAGS) -o $@ $^


# Inclusion automatique des fichiers de dépendances générés (.d)
-include $(DEPS)


# Compilation des .o dans le dossier build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CPP) $(CXXFLAGS) -c $< -o $@


# Nettoyage des fichiers objets et dépendances
clean:
	rm -f $(OBJECTS) $(DEPS)


# Nettoyage complet
fclean: clean
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR) $(BIN_DIR)


# Rebuild complet
re: fclean all

# Création des dossiers nécessaires
$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Exécution rapide
run: all
	./$(TARGET)


.PHONY: all clean fclean re run
