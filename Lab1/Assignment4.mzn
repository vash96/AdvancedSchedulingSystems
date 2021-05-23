include "count_eq.mzn";

%%%% Input data
int: Warehouses;
int: Stores;
array [1..Warehouses] of int: Capacity;
array [1..Warehouses] of int: FixedCost;
array [1..Stores] of int: Goods;
array [1..Stores, 1..Warehouses] of int: SupplyCost;

%%%% Input-dependent constants
int: MaxQuantity = min ( max(Goods), max(Capacity) ); % Max quantity that can be supplied
int: MaxCost = sum (FixedCost) + sum (Goods) * max (SupplyCost);


%%%% Problem variables
array [1..Stores, 1..Warehouses] of var 0..MaxQuantity: Supply; % How many goods to store from warehouse
array [1..Warehouses] of var bool: IsOpen; % If warehouse has been opened

%%%% Problem dependent constraints
%   1. The total quantity of goods taken from a warehouse cannot exceed its capacity.
% + 3. Goods can be moved only from open warehouses.
constraint
    forall (w in 1..Warehouses)
        (sum ([Supply[s, w] | s in 1..Stores]) <= Capacity[w] * IsOpen[w]);

% 2. The total quantity of goods brought to a store must be exactly equal to its request.
constraint
    forall (s in 1..Stores)
        (sum ([Supply[s, w] | w in 1..Warehouses]) = Goods[s]);

% 4. Each store is supplied by exactly one warehouse.
constraint
    forall(s in 1..Stores)
        (count_eq ([Supply[s, w] | w in 1..Warehouses], 0, Warehouses-1));


%%%% Objective function
var 0..MaxCost: Objective;

constraint
    Objective =
        sum (w in 1..Warehouses)
            (IsOpen[w]*FixedCost[w] + sum ([Supply[s, w] * SupplyCost[s, w] | s in 1..Stores]));

%%% Solve
solve :: int_search(Supply, smallest, indomain_min)
    minimize Objective;


%%%% Output
output ["\(Objective)\n"];