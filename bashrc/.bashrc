#!/bin/sh

export PS1=" \033[36m\w\033[34m O_o \033[0m"

alias ls='ls --color'
alias g="git"
alias c="clear"
alias wmconf="vim ~/.config/dwl/config.h"
alias wifi="impala"
alias dv="doas vim"
alias ff="fastfetch --config ~/.config/fastfetch/gentoo.jsonc"
alias weather="curl 'wttr.in/Tyumen'"

sheet() {
    curl "cheat.sh/$*"
}

super() {
    su -c "sh -c '$*'"
}
complete -c super

bind '"\C-h": backward-kill-word'
bind '"\e[127;5u": backward-kill-word'
bind '"\e[3;5~": kill-word'

#on_exit() {
    #printf "\e[?25l"
#}
#trap on_exit EXIT

translate() {
    curl -sA "Mozilla/5.0" \
        -d "client=gtx" -d "sl=auto" -d "tl=$1" -d "dt=t" \
        --data-urlencode "q=$2" \
        "https://translate.googleapis.com/translate_a/single" \
        | grep -o '"[^"]*"' | head -1 | tr -d '"'
}

builds() {
    shopt -s nullglob
    for d in ~/build/*/; do
        [ -d "$d" ] || continue
        
        local proj=$(basename "$d")
        
        local tgz=$(find "$d" -maxdepth 1 \( -name "*.tar.*" -o -name "*.tgz" -o -name "*.zip" \) -exec basename {} \; | xargs)
        local dirs=$(find "$d" -mindepth 1 -maxdepth 1 -type d -exec basename {} \; | xargs)
        
        echo "$proj: [tarballs: $tgz] [dirs: $dirs]"
    done
    shopt -u nullglob
}
