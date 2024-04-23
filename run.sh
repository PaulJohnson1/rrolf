# Copyright (C) 2024  Paul Johnson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

gdb -ex "set pagination 0" -ex "run" -ex "generate-core-file" -ex "quit" --batch /app/rrolf-server

# gdb -ex "set pagination 0" -ex "run" -ex "bt" -ex "info registers" -ex "quit" --batch /app/generate_core_dump

gdb -c core.* -ex "bt" -ex "quit" /app/rrolf-server

du -h core.*