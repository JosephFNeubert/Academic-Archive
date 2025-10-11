"""
File: Neubert_Module2.py
Author: Joseph Neubert
Description: A program that implements four school-related classes
"""

from dataclasses import dataclass


class Student:
    def __init__(
        self, name: str, student_id: int, student_name: str, marks: int
    ) -> None:
        self.name = name
        self.student_id = student_id
        self.student_name = student_name
        self.marks = marks


class Undergraduate(Student):
    def __init__(
        self, name: str, student_id: int, student_name: str, marks: int, sat_score: int
    ) -> None:
        super().__init__(name, student_id, student_name, marks)
        self.sat_score = sat_score

    def __eq__(self, __o: object) -> bool:
        if (
            isinstance(__o, Undergraduate)
            and __o.name == self.name
            and __o.student_id == self.student_id
            and __o.marks == self.marks
            and __o.sat_score == self.sat_score
        ):
            return True
        else:
            return False

    def __repr__(self) -> str:
        return f"An undergraduate student named {self.name} with the student I.D {self.student_id}. Their marks are {self.marks} and earned a SAT score of {self.sat_score}."


class Postgraduate(Student):
    def __init__(
        self,
        name: str,
        student_id: int,
        student_name: str,
        marks: int,
        bachelors_gpa: float,
    ) -> None:
        super().__init__(name, student_id, student_name, marks)
        self.bachelors_gpa = bachelors_gpa

    def __eq__(self, __o: object):
        if (
            isinstance(__o, Postgraduate)
            and __o.name == self.name
            and __o.student_id == self.student_id
            and __o.marks == self.marks
            and __o.bachelors_gpa == self.bachelors_gpa
        ):
            return True
        else:
            return False

    def __repr__(self) -> str:
        return f"A postgraduate student named {self.name} with the student I.D {self.student_id}. Their marks are {self.marks} and earned a college GPA of {self.bachelors_gpa}."


@dataclass
class Marks:
    marks: int

    def value(self) -> int:
        return self.marks


x = Undergraduate("Mark", 1, "Mark", Marks(100).value(), 1580)
y = Postgraduate("Sam", 2, "Sam", Marks(90).value(), 3.2)
z = Undergraduate("Mark", 1, "Mark", Marks(100).value(), 1580)

print(isinstance(x, Undergraduate))
print(isinstance(y, Postgraduate))
print(x == y)
print(x == z)
print("")

student_list = [x, y, z]
for i in student_list:
    print(i)
