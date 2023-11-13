BUILD_DIR=build
BIN_DIR=bin
POT_DIR=pot

TARGET=$(BIN_DIR)/i18n

.PHONY: all distclean

all: $(TARGET) $(POT_DIR)/ru/LC_MESSAGES/i18n.mo

$(TARGET):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	cd $(BUILD_DIR) && cmake .. && make

i18n.pot: main.c
	xgettext --keyword=_ $< -o $@

po/ru.po: i18n.pot
	msginit -i i18n.pot -o $@ -l ru_RU.UTF-8

pot/ru/LC_MESSAGES/i18n.mo: po/ru.po
	mkdir -p pot/ru/LC_MESSAGES
	msgfmt -o $@ $<

distclean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(POT_DIR)
