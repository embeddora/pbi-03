RED='\033[0;31m'
NC='\033[0m'

echo -e "Running ${RED}autoconf${NC}..."

autoconf configure.ac > configure

chmod +x configure

echo -e "Running ${RED}configure${NC}..."

./configure

echo -e "${RED}Making${NC} a project"

make
