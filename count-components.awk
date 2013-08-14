# Purpose: Count the number of component names in the last column and write the
#    count at the beginning of the line
#
# Usage:
# sort -k2 bom.txt | awk -e 'BEGIN { OFS="\t"; }' -E merge-components.awk | \
#  awk -F"\t" -e 'BEGIN { OFS="\t"; }' -E count-components.awk
# where bom.txt is an Eagle BOM list text export.
{
  count = gsub(",",",",$5) + 1;
  print count, $0;
}
