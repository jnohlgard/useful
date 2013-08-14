# Purpose: Moves component name from the first column into the final column and
#   merges identical component values into a single line.
#
# Usage: sort -k2 bom.txt | awk -E thisfile.awk
# where bom.txt is an Eagle BOM list text export.
BEGIN {
  compvalue = "";
  namebuf = "";
}
{
  if ($2 OFS $3 OFS $4 OFS $5 != compvalue)
  {
    print compvalue, namebuf;
    namebuf = $1;
    compvalue = $2 OFS $3 OFS $4 OFS $5;
  }
  else
  {
    namebuf = namebuf "," $1;
  }
}
