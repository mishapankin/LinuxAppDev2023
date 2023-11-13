#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("i18n", "pot");
    textdomain("i18n");

    printf(_("Guess a number from 1 to 100\n"));

    int left = 1, right = 100;

    while (left < right) {
        int mid = (left + right) / 2;
        printf(_("Is the number greater than %d? (y/n)\n"), mid);
        char answer[1000];
        scanf("%s", answer);

        if (answer[0] == 'y' || answer[0] == 'Y') {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf(_("Your number is %d\n"), left);

    return 0;
}
