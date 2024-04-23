gdb -ex "set pagination 0" -ex "run" -ex "generate-core-file" -ex "quit" --batch /app/rrolf-server

# gdb -ex "set pagination 0" -ex "run" -ex "bt" -ex "info registers" -ex "quit" --batch /app/generate_core_dump

gdb -c core.* -ex "bt" -ex "quit" /app/rrolf-server

du -h core.*