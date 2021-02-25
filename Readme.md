# Scores
## Total score : 728,533,819 points

A – Example : **50 points**
B – A little bit of everything : **11,811 points**
C – Many ingredients : **709,604,989 points**
D – Many pizzas : **7,995,137 points**
E – Many teams : **10,921,832 points**

## Logic used
1. Choose tthe largest ingredients pizza
2. I used a certain **factor = union - intersection** , which is a factor to determine
the extent upto which we have more union and lesser intersection.
And choose corresponding pizzas which gives maximum factor.

This , on testing, worked better than the approach in which only union is maximised,
as I took intersection and union extents into account just by using this factor.