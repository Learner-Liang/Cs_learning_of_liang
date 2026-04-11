import numpy as np
class MultiplyLayer:
    def __init__(self):
        self.x = None
        self.y = None
    def forward(self, x, y):
        self.x = x
        self.y = y
        out = x * y
        return out
    def backward(self, dout):
        dx=dout * self.y
        dy=dout * self.x
        return dx, dy


class AddLayer:
    def __init__(self):
        pass
    def forward(self, x, y):
        out = x + y
        return out
    def backward(self, dout):
        dx = dout * 1
        dy = dout * 1
        return dx, dy
    

# 乘法层的测试：买苹果案例道德实例化
if __name__ == "__main__":
    buy_apple_layer = MultiplyLayer()
    apple_tax_layer = MultiplyLayer()
    # 前向
    apple_price = 100
    apple_num = 2
    consuptionn_tax = 1.1
    sum = buy_apple_layer.forward(apple_price, apple_num)
    sum_price = apple_tax_layer.forward(sum, consuptionn_tax)
    print("总价：", f"{sum_price:.4f}")
    # 反向
    sum, consuptionn_tax = apple_tax_layer.backward(1)
    a,b= buy_apple_layer.backward(sum)
    print(f"{a:.4f} , {b:.4f}")


# 乘法与家法综合测试
if __name__ == "__main__":
    buy_apple_layer = MultiplyLayer()
    tax_layer = MultiplyLayer()
    buy_orange_layer = MultiplyLayer()
    add_apple_orange_layer = AddLayer()

    apple_price = 100
    apple_num = 2
    orange_price = 150
    orange_num = 3
    consuptionn_tax = 1.1
    # 向前
    apple_sum = buy_apple_layer.forward(apple_price, apple_num)
    orange_sum = buy_orange_layer.forward(orange_price, orange_num)
    all_sum = add_apple_orange_layer.forward(apple_sum, orange_sum)
    all_sum_price = tax_layer.forward(all_sum, consuptionn_tax)
    print("总价：", f"{all_sum_price:.4f}")
    # 向后

    a,b= tax_layer.backward(1)
    print(f"消费税反向传播：{b:.4f}")
    a,b=add_apple_orange_layer.backward(a)
    c,d=buy_apple_layer.backward(a)
    print(f"苹果价格反向传播：{c:.4f}")
    print(f"苹果数量反向传播：{d:.4f}")

    e,f=buy_orange_layer.backward(b)
    print(f"橘子价格反向传播：{e:.4f}")
    print(f"橘子数量反向传播：{f:.4f}") 







