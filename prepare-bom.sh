sed -e '1,+9d' -e '/^[\s]*$/d' "$1" | sort -k2 | awk -e 'BEGIN { OFS="\t"; }' -E merge-components.awk | awk -e 'BEGIN { OFS="\t"; }' -E count-components.awk
