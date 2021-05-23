%%%%
% Read Assignment5.mzn first
%
% This model provides a faster way to solve WLP through CoinBC solver.
% The difference in performance is significant:
%   * wlp-100 with Assignment5.mzn takes 2m30s on CoinBC to achieve and prove optimality
%   * wlp-100 with this model takes only 16 seconds on CoinBC to achieve and prove optimality
%
% On Gecode and Chuffed this model is complete garbage (solutions found are ~6x higher than optimum)
%
% The model "merges" Assignment5 view of SuppliedBy vector and Assignment4 view of matrix Supply:
% channelling constraint at line 52-54 achieve this merge.
%%%%

include "count_eq.mzn";

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
array [1..Stores, 1..Warehouses] of var 0..MaxQuantity: Supply;

%%%% Problem-dependent constraints
%   1. The total quantity of goods taken from a warehouse cannot exceed its capacity.
% + 3. Goods can be moved only from open warehouses.
constraint
    forall (w in 1..Warehouses)
        (sum ([Supply[s, w] | s in 1..Stores])
            <= Capacity[w] * IsOpen[w]);

% 2. The total quantity of goods brought to a store must be exactly equal to its request.
% Full assign constraint already given as objective definition

%%%% Redundant constraints
constraint
    forall(s in 1..Stores)
        (count_eq ([Supply[s, w] | w in 1..Warehouses], 0, Warehouses-1));

%%%% Channelling
constraint
    forall (s in 1..Stores, w in 1..Warehouses)
        (Supply[s, w] = Goods[s] * (SuppliedBy[s] = w));

%%%% Objective function
var 0..MaxCost: Objective;
constraint
    Objective =
        sum (w in 1..Warehouses)
            (IsOpen[w]*FixedCost[w] + sum ([Supply[s, w] * SupplyCost[s, w] | s in 1..Stores]));

%%% Solve
solve :: int_search(Supply, dom_w_deg, indomain_min)
        minimize Objective;


%%%% Output
output ["\(Objective)\n"];