module ports1 (x, y, z, y);  // Error
  input x;
  output reg y;
  output     y;  // Error
endmodule

module ports2 (x, y);
  input x;
  always @(x) y <= x; // OK
  output reg y;
endmodule // ports2
