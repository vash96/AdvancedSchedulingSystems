include "bin_packing_load.mzn";

%%%% Input data
int: Warehouses;
int: Stores;
array [1..Warehouses] of int: Capacity;
array [1..Warehouses] of int: FixedCost;
array [1..Stores] of int: Goods;
array [1..Stores, 1..Warehouses] of int: SupplyCost;

%%%% Input-dependent constants
int: MaxCost = sum (FixedCost) + sum (Goods) * max (SupplyCost); % Max objective cost
int: MaxCapacity = max (Capacity);
int: MaxQuantity = min( MaxCapacity, max(Goods) );

%%%% Problem variables
array [1..Stores] of var 1..Warehouses: SuppliedBy; % Which warehouse supplies given store
array [1..Warehouses] of var bool: IsOpen; % If warehouse has been open
array [1..Warehouses] of var 0..MaxCapacity: Load; % Load of warehouse
array [1..Stores] of var 0..max(SupplyCost)*max(Goods): Cost; % Cost[s] = Goods[s] * SupplyCost[s, SuppliedBy[s]]

%%%% Problem-dependent constraints
% Assignment 5 has been modeled as a variant of Bin Packing
constraint
    bin_packing_load(
        Load,
        SuppliedBy,
        Goods
    );

%%%% Channelling
% Load cannot exceed Capacity (given also open-condition)
constraint
    forall(w in 1..Warehouses)
        (Load[w] <= Capacity[w] * IsOpen[w]);

% Cost[s] as by definition
constraint
    forall(s in 1..Stores)
        (Cost[s] = Goods[s] * SupplyCost[s, SuppliedBy[s]]);

%%%% Objective function
var 0..MaxCost: Objective;
constraint
    Objective =
        sum (w in 1..Warehouses)
            (IsOpen[w]*FixedCost[w])
        +
        sum (Cost);

%%% Solve
solve :: int_search(Cost, smallest, indomain_min)
        minimize Objective;


%%%% Output
output ["\(Objective)\n"];