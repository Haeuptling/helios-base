#!/bin/bash

max_runs=30
counter=0

script_name="quickStart.sh"

while [ $counter -lt $max_runs ]; do
    echo "Starte Durchlauf $((counter + 1)) von $max_runs"
    
    bash $script_name
    
    counter=$((counter + 1))
    

done

echo "Das Skript wurde $max_runs mal ausgeführt."
